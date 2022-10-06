#include "Predicate.h"

Predicate::Predicate(std::string startingID) {
    this->startingID = startingID;
}

Predicate::~Predicate() {
    for (auto & i : parameterList) {
        delete i;
    }
}

std::string Predicate::toString() {
    std::string output = startingID + "(";
    for (unsigned int i = 0; i < parameterList.size(); i++) {
        output += parameterList.at(i)->toString() + (i < parameterList.size() - 1 ? "," : "");
    }
    return output + ")";

}

void Predicate::addParameter(Parameter *newParam) {
    parameterList.push_back(newParam);
}
