#ifndef RULE_H
#define RULE_H

#include <string>
#include <vector>

#include "Predicate.h"


class Rule {
private:
    Predicate* headPredicate;
    std::vector<Predicate*> predicateList;
public:
    Rule(Predicate* headPredicate);
    ~Rule();
    std::string toString();
    void addPredicate(Predicate* newPredicate);
    Predicate* getHeadPredicate() {
        return headPredicate;
    }
    std::vector<Predicate*> getPredicateList() {
        return predicateList;
    }
};


#endif // RULE_H
