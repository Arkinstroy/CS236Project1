#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

class Parameter {
private:
    std::string content;
public:
    Parameter(std::string content);
    std::string toString();
    bool isConstant() {
        return content[0] == '\'';
    }
};


#endif // PARAMETER_H
