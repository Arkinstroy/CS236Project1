#include "Interpreter.h"

#include <iostream>

void Interpreter::InterpretSchemes() {
    for (auto & i : program->schemeList) {
        Header newHeader;
        for (auto & j : i->parameterList) {
            newHeader.addColumnName(j->toString());
        }
        Relation* newRelation = new Relation(i->getStartingID(), newHeader);
        database->AddRelation(newRelation);
        delete newRelation;
    }
}

void Interpreter::InterpretFacts() {
    for (auto & i : program->factList) {
        Relation* relation = database->GetRelation(i->getStartingID());
        Tuple newTuple;
        for (auto & j : i->parameterList) {
            newTuple.addValue(j->toString());
        }
        relation->AddTuple(newTuple);
    }
}

void Interpreter::InterpretRules() {

}

void Interpreter::InterpretQueries() {
    for (auto & i : program->queryList) {
        Relation relation = database->GetRelationCopy(i->getStartingID());
        for (unsigned int j = 0; j < i->parameterList.size(); j++) {
            std::string param = i->parameterList.at(j)->toString();
            if (i->parameterList.at(j)->isConstant()) {
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
        outputString += i->toString() + "? ";
        if (relation.getTupleSize() > 0) {
            outputString += "Yes(" + std::to_string(relation.getTupleSize()) + ")\n";
        } else {
            outputString += "No\n";
        }
        outputString += relation.toString();
        firstIndices.clear();
        variables.clear();
        markedIDs.clear();
    }
}

void Interpreter::interpret() {
    InterpretSchemes();
    InterpretFacts();
    InterpretQueries();
}

void Interpreter::outputResults() {
    std::cout << outputString;
}
