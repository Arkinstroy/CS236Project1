#include "Lexer.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();

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

    std::cout << inputString;

    lexer->Run(inputString);



    delete lexer;

    return 0;
}