#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>

class Tuple {
public:
    std::vector<std::string> rowValues;
    void addValue(std::string value) {
        rowValues.push_back(value);
    }

    bool operator<(const Tuple &rhs) const {
        return rowValues < rhs.rowValues;
    }

    bool operator>(const Tuple &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Tuple &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Tuple &rhs) const {
        return !(*this < rhs);
    }
};


#endif // TUPLE_H
