#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H

#include <vector>
#include <string>
#include <set>

#include "Rule.h"
#include "Predicate.h"


class DatalogProgram {
private:
    std::string failMessage;

public:
    DatalogProgram();
    ~DatalogProgram();

    void outputResults();
    void setFailMessage(std::string message);
    std::vector<Predicate*> schemeList;
    std::vector<Predicate*> factList;
    std::vector<Rule*> ruleList;
    std::vector<Predicate*> queryList;
    std::set<std::string> domain;
};


#endif // DATALOGPROGRAM_H
