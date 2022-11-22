#include "Interpreter.h"

#include <iostream>
#include <set>

void Interpreter::InterpretSchemes() {
    for (auto & scheme : program->schemeList) {
        Header newHeader;
        for (auto & j : scheme->parameterList) {
            newHeader.addColumnName(j->toString());
        }
        Relation* newRelation = new Relation(scheme->getStartingID(), newHeader);
        database->AddRelation(newRelation);
        delete newRelation;
    }
}

void Interpreter::InterpretFacts() {
    for (auto & fact : program->factList) {
        Relation* relation = database->GetRelation(fact->getStartingID());
        Tuple newTuple;
        for (auto & j : fact->parameterList) {
            newTuple.addValue(j->toString());
        }
        relation->AddTuple(newTuple);
    }
}

void Interpreter::InterpretRules() {
    bool changed = true;
    passes = 0;
    while (changed) {
        passes++;
        changed = false;
        for (auto & rule : program->ruleList) {
            std::vector<Relation> relations;
            for (auto & predicate : rule->getPredicateList()) {
                Relation relation = database->GetRelationCopy(predicate->getStartingID());
                for (unsigned int j = 0; j < predicate->parameterList.size(); j++) {
                    std::string param = predicate->parameterList.at(j)->toString();
                    if (predicate->parameterList.at(j)->isConstant()) {
                        relation = relation.select1(j, param);
                    } else {
                        if (markedIDs.find(param) != markedIDs.end()) {
                            relation = relation.select2(markedIDs[param], j);
                        } else {
                            markedIDs[param] = j;
                            firstIndices.push_back(j);
                            variables.push_back(param);
                        }
                    }
                }
                relation = relation.project(firstIndices);
                relation = relation.rename(variables);
                relations.push_back(relation);
                firstIndices.clear();
                variables.clear();
                markedIDs.clear();
            }
            if (!relations.empty()) {
                Relation finalRelation = relations.at(0);
                for (unsigned int i = 1; i < relations.size(); i++) {
                    finalRelation = finalRelation.Join(relations.at(i));
                }
                std::vector<std::string> paramsInHeadVec;
                std::vector<unsigned int> columnsToProject;
                for (auto & param : rule->getHeadPredicate()->parameterList) {
                    paramsInHeadVec.push_back(param->toString());
                    for (unsigned int i = 0; i < finalRelation.getHeaderSize(); i++) {
                        if (param->toString() == finalRelation.getColumn(i)) {
                            columnsToProject.push_back(i);
                        }
                    }
                }
                finalRelation = finalRelation.project(columnsToProject);
                finalRelation = finalRelation.rename(paramsInHeadVec);
                Relation* relationToGet = database->GetRelation(rule->getHeadPredicate()->getStartingID());
                unsigned int sizeBefore = relationToGet->getTupleSize();
                ruleOutput += rule->toString() + "\n";
                ruleOutput += relationToGet->unionize(finalRelation);
                if (sizeBefore != relationToGet->getTupleSize()) {
                    changed = true;
                }
            }
        }
    }
}

void Interpreter::InterpretQueries() {
    for (auto & query : program->queryList) {
        Relation relation = database->GetRelationCopy(query->getStartingID());
        for (unsigned int j = 0; j < query->parameterList.size(); j++) {
            std::string param = query->parameterList.at(j)->toString();
            if (query->parameterList.at(j)->isConstant()) {
                relation = relation.select1(j, param);
            } else {
                if (markedIDs.find(param) != markedIDs.end()) {
                    relation = relation.select2(markedIDs[param], j);
                } else {
                    markedIDs[param] = j;
                    firstIndices.push_back(j);
                    variables.push_back(param);
                }
            }
        }
        relation = relation.project(firstIndices);
        relation = relation.rename(variables);
        queryOutput += query->toString() + "? ";
        if (relation.getTupleSize() > 0) {
            queryOutput += "Yes(" + std::to_string(relation.getTupleSize()) + ")\n";
        } else {
            queryOutput += "No\n";
        }
        queryOutput += relation.toString();
        firstIndices.clear();
        variables.clear();
        markedIDs.clear();
    }
}

void Interpreter::interpret() {
    InterpretSchemes();
    InterpretFacts();
    InterpretRules();
    InterpretQueries();
}

void Interpreter::outputResults() {
    std::cout << "Rule Evaluation" << std::endl;
    std::cout << ruleOutput << std::endl;
    std::cout << "Schemes populated after " << passes << " passes through the Rules.\n" << std::endl;
    std::cout << "Query Evaluation" << std::endl;
    std::cout << queryOutput;
}
