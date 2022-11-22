#ifndef RELATION_H
#define RELATION_H

#include "Tuple.h"
#include "Header.h"
#include <set>
#include <map>
#include <string>
#include <vector>

class Relation {
private:
    std::string name;
    Header columnNames;
    std::set<Tuple> tuples;
    Header combineHeaders(Header& header1, Header& header2, std::map<unsigned int, unsigned int>& sourceMap, std::vector<unsigned int>& uniqueIndices);
    bool isJoinable(Tuple& tuple1, Tuple& tuple2, std::map<unsigned int, unsigned int>& sourceMap);
    Tuple combineTuples(Tuple& tuple1, Tuple& tuple2, std::vector<unsigned int>& uniqueIndices);
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
    unsigned int getHeaderSize() {
        return columnNames.getSize();
    }
    std::string getColumn(unsigned int index) {
        return columnNames.getColumn(index);
    }

    std::string toString();

    Relation select1(unsigned int columnIndex, std::string value);
    Relation select2(unsigned int columnIndex1, unsigned int columnIndex2);
    Relation project(std::vector<unsigned int>& columnsToProject);
    Relation rename(std::vector<std::string>& newColumnNames);
    Relation Join(Relation other);
    std::string unionize(Relation other);
};


#endif // RELATION_H
