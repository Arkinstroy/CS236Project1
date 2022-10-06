#include "DatalogProgram.h"

#include <iostream>

DatalogProgram::DatalogProgram() {

}

DatalogProgram::~DatalogProgram() {
    for (auto &i: schemeList) {
        delete i;
    }
    for (auto &i: factList) {
        delete i;
    }
    for (auto &i: ruleList) {
        delete i;
    }
    for (auto &i: queryList) {
        delete i;
    }
}

void DatalogProgram::outputResults() {
    if (failMessage == "") {
        std::cout << "Success!" << std::endl;
        std::cout << "Schemes(" << schemeList.size() << "):" << std::endl;
        for (auto &i: schemeList) {
            std::cout << "  " << i->toString() << std::endl;
        }
        std::cout << "Facts(" << factList.size() << "):" << std::endl;
        for (auto &i: factList) {
            std::cout << "  " << i->toString() << "." << std::endl;
        }
        std::cout << "Rules(" << ruleList.size() << "):" << std::endl;
        for (auto &i: ruleList) {
            std::cout << "  " << i->toString() << std::endl;
        }
        std::cout << "Queries(" << queryList.size() << "):" << std::endl;
        for (auto &i: queryList) {
            std::cout << "  " << i->toString() << "?" << std::endl;
        }
        std::cout << "Domain(" << domain.size() << "):" << std::endl;
        for (auto &i: domain) {
            std::cout << "  " << i << std::endl;
        }
    }
    else {
        std::cout << "Failure!" << std::endl;
        std::cout << "  " << failMessage << std::endl;
    }
}

void DatalogProgram::setFailMessage(std::string message) {
    failMessage = message;
}
