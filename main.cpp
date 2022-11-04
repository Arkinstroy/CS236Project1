#include "Lexer.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Interpreter.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();
    Parser* parser = new Parser();

    DatalogProgram* datalogProgram;

    std::string filename = argv[1];
    std::ifstream infile;
    infile.open(filename, std::ifstream::in);

    std::string inputString;
    bool hitEOF = false;
    char input;
    while(!hitEOF) {
        infile.get(input);
        inputString += input;
        if (infile.peek() == EOF) {
            hitEOF = true;
        }
    }
    infile.close();


    lexer->Run(inputString);

    //lexer->OutputResults();

    datalogProgram = parser->parse(lexer);

    //datalogProgram->outputResults();

    Interpreter* interpreter = new Interpreter(datalogProgram);

    interpreter->interpret();

    interpreter->outputResults();

    delete datalogProgram;
    delete lexer;
    delete parser;

    return 0;
}