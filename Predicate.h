#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
private:
    std::string startingID;
public:
    Predicate(std::string startingID);
    ~Predicate();
    std::string toString();
    void addParameter(Parameter* newParam);
    std::vector<Parameter*> parameterList;
    std::string getStartingID() {
        return startingID;
    }
};


#endif // PREDICATE_H
