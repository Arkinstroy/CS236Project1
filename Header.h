#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>


class Header {
private:
    std::vector<std::string> columnNames;
public:
    Header() = default;
    Header(std::vector<std::string>& columnNames) {
        this->columnNames = columnNames;
    }
    std::string getColumn(unsigned int index) {
        return columnNames.at(index);
    }
    unsigned int getSize() {
        return columnNames.size();
    }
    void addColumnName(std::string name) {
        this->columnNames.push_back(name);
    }

};


#endif // HEADER_H
