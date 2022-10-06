#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

class Parameter {
private:
    std::string content;
public:
    Parameter(std::string content);
    std::string toString();
};


#endif // PARAMETER_H
