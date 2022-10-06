#ifndef RULE_H
#define RULE_H

#include <string>
#include <vector>

#include "Predicate.h"


class Rule {
private:
    std::string headPredicate;
    std::vector<Predicate*> predicateList;
public:
    Rule(std::string headPredicate);
    ~Rule();
    std::string toString();
    void addPredicate(Predicate* newPredicate);
};


#endif // RULE_H
