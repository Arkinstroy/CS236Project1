#include "Rule.h"

Rule::Rule(Predicate* headPredicate) {
    this->headPredicate = headPredicate;
}

Rule::~Rule() {
    for (auto & i : predicateList) {
        delete i;
    }
}

void Rule::addPredicate(Predicate* newPredicate) {
    predicateList.push_back(newPredicate);
}

std::string Rule::toString() {
    std::string output = this->headPredicate->toString() + " :- ";
    for (unsigned int i = 0; i < predicateList.size(); i++) {
        output += predicateList.at(i)->toString() += (i < predicateList.size() - 1 ? "," : "");
    }
    return output + ".";
}