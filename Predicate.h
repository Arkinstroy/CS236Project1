#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
private:
    std::string startingID;
    std::vector<Parameter*> parameterList;
public:
    Predicate(std::string startingID);
    ~Predicate();
    std::string toString();
    void addParameter(Parameter* newParam);
};


#endif // PREDICATE_H
