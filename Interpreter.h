#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include <map>
#include <string>
#include <vector>

class Interpreter {
private:
    DatalogProgram* program;
    Database* database;
    std::map<std::string, unsigned int> markedIDs;
    std::vector<unsigned int> firstIndices;
    std::vector<std::string> variables;
    std::string outputString;
public:
    Interpreter(DatalogProgram* program) {
        this->program = program;
        this->database = new Database();
    }
    void InterpretSchemes();
    void InterpretFacts();
    void InterpretRules();
    void InterpretQueries();

    void interpret();
    void outputResults();
};


#endif // INTERPRETER_H
