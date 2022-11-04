#ifndef RELATION_H
#define RELATION_H

#include "Tuple.h"
#include "Header.h"
#include <set>
#include <string>
#include <vector>

class Relation {
private:
    std::string name;
    Header columnNames;
    std::set<Tuple> tuples;
public:
    Relation() = default;
    Relation(std::string name, Header columnNames) {
        this->name = name;
        this->columnNames = columnNames;
    }
    std::string GetName() {
        return name;
    }
    unsigned int getTupleSize() {
        return tuples.size();
    }
    void AddTuple(Tuple newTuple) {
        tuples.insert(newTuple);
    }

    std::string toString();

    Relation select1(unsigned int columnIndex, std::string value);
    Relation select2(unsigned int columnIndex1, unsigned int columnIndex2);
    Relation project(std::vector<unsigned int>& columnsToProject);
    Relation rename(std::vector<std::string>& newColumnNames);
    Relation Join(Relation other);
};


#endif // RELATION_H
