#include "Lexer.h"
#include <fstream>

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();

    string filename = argv[1];
    std::ifstream infile(filename);

    delete lexer;

    return 0;
}