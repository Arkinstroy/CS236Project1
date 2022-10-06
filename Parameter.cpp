#include "Parameter.h"

Parameter::Parameter(std::string content) {
    this->content = content;
}

std::string Parameter::toString() {
    return content;
}