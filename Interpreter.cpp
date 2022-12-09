#include "Interpreter.h"
#include "Graph.h"

#include <iostream>
#include <set>
#include <map>

void Interpreter::InterpretSchemes() {
    for (Predicate* & scheme : program->schemeList) {
        Header newHeader;
        for (Parameter* & j : scheme->parameterList) {
            newHeader.addColumnName(j->toString());
        }
        Relation* newRelation = new Relation(scheme->getStartingID(), newHeader);
        database->AddRelation(newRelation);
        delete newRelation;
    }
}

void Interpreter::InterpretFacts() {
    for (Predicate* & fact : program->factList) {
        Relation* relation = database->GetRelation(fact->getStartingID());
        Tuple newTuple;
        for (Parameter* & j : fact->parameterList) {
            newTuple.addValue(j->toString());
        }
        relation->AddTuple(newTuple);
    }
}

void Interpreter::InterpretRules() {
    forwardGraph = new Graph();
    reverseGraph = new Graph();
    std::vector<std::string> startingIDs;
    std::map<std::string, std::vector<unsigned int>> idMap;
    for (unsigned int i = 0; i < program->ruleList.size(); i++) {
        forwardGraph->addNode(i);
        reverseGraph->addNode(i);
        std::string startingID = program->ruleList.at(i)->getHeadPredicate()->getStartingID();
        if (idMap.count(startingID)) {
            idMap[startingID].push_back(i);
        } else {
            idMap[startingID] = std::vector<unsigned int>();
            idMap[startingID].push_back(i);
        }
    }
    for (unsigned int i = 0; i < program->ruleList.size(); i++) {
        for (Predicate* & predicate : program->ruleList.at(i)->getPredicateList()) {
            std::string startingID = predicate->getStartingID();
            if (idMap.count(startingID)) {
                for (unsigned int j = 0; j < idMap[startingID].size(); j++) {
                    forwardGraph->addRelation(i, idMap[startingID].at(j));
                    reverseGraph->addRelation(idMap[startingID].at(j), i);
                }
            }
        }
    }
    //reverseGraph = forwardGraph->reverse();
//    forwardGraph->printAdjacency();
    //reverseGraph->printAdjacency();
    std::vector<unsigned int> postOrder;
    reverseGraph->DFSF(postOrder);
//    for (unsigned int i = 0; i < postOrder.size(); i++) {
//        std::cout << postOrder.at(i) << " ";
//    }
//    std::cout << std::endl;

    std::vector<unsigned int> reversePostOrder;
    for (unsigned int i = postOrder.size(); i > 0; i--) {
        reversePostOrder.push_back(postOrder.at(i - 1));
    }

//    for (unsigned int i = 0; i < reversePostOrder.size(); i++) {
//        std::cout << reversePostOrder.at(i) << " ";
//    }
//    std::cout << std::endl;
    forwardGraph->DFSFscc(reversePostOrder);
//    forwardGraph->printSCCs();

    for (unsigned int i = 0; i < forwardGraph->getSCCSize(); i++) {
        bool changed = true;
        passes = 0;
        ruleOutput += "SCC: " + forwardGraph->sccToSring(i) + "\n";
        std::vector<Rule*> ruleList;
        std::set<unsigned int> currentSCC = forwardGraph->getsccs(i);
        for (unsigned int j = 0; j < program->ruleList.size(); j++) {
            if (currentSCC.find(j) != currentSCC.end()) {
                ruleList.push_back(program->ruleList.at(j));
            }
        }
        while (changed) {
            passes++;
            changed = false;
            for (Rule *&rule: ruleList) {
                std::vector<Relation> relations;
                for (Predicate *&predicate: rule->getPredicateList()) {
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
                    for (unsigned int k = 1; k < relations.size(); k++) {
                        finalRelation = finalRelation.Join(relations.at(k));
                    }
                    std::vector<std::string> paramsInHeadVec;
                    std::vector<unsigned int> columnsToProject;
                    for (Parameter *&param: rule->getHeadPredicate()->parameterList) {
                        paramsInHeadVec.push_back(param->toString());
                        for (unsigned int k = 0; k < finalRelation.getHeaderSize(); k++) {
                            if (param->toString() == finalRelation.getColumn(k)) {
                                columnsToProject.push_back(k);
                            }
                        }
                    }
                    finalRelation = finalRelation.project(columnsToProject);
                    finalRelation = finalRelation.rename(paramsInHeadVec);
                    Relation *relationToGet = database->GetRelation(rule->getHeadPredicate()->getStartingID());
                    unsigned int sizeBefore = relationToGet->getTupleSize();
                    ruleOutput += rule->toString() + "\n";
                    ruleOutput += relationToGet->unionize(finalRelation);
                    if (sizeBefore != relationToGet->getTupleSize()) {
                        changed = true;
                    }
                    if (forwardGraph->hasSelfLoop(i)) {
                        changed = false;
                    }
                }
            }
        }
        ruleOutput += std::to_string(passes) + " passes: " + forwardGraph->sccToSring(i) + "\n";
    }
}

void Interpreter::InterpretQueries() {
    for (Predicate* & query : program->queryList) {
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
    std::cout << "Dependency Graph" << std::endl;
    forwardGraph->printAdjacency();
    std::cout << std::endl << "Rule Evaluation" << std::endl;
    std::cout << ruleOutput << std::endl;
    std::cout << "Query Evaluation" << std::endl;
    std::cout << queryOutput;
}
