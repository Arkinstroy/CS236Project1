#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"
#include <map>
#include <string>
#include <vector>

class Interpreter {
private:
    DatalogProgram* program;
    Database* database;
    Graph* forwardGraph;
    Graph* reverseGraph;
    std::map<std::string, unsigned int> markedIDs;
    std::vector<unsigned int> firstIndices;
    std::vector<std::string> variables;
    std::string queryOutput;
    unsigned int passes;
    std::string ruleOutput;
public:
    Interpreter(DatalogProgram* program) {
        this->program = program;
        this->database = new Database();
    }
    ~Interpreter() {
        delete program;
        delete database;
    }
    void InterpretSchemes();
    void InterpretFacts();
    void InterpretRules();
    void InterpretQueries();

    void interpret();
    void outputResults();
};


#endif // INTERPRETER_H
