#include "Relation.h"

#include <string>
#include <vector>
#include <map>

Relation Relation::select1(unsigned int columnIndex, std::string value) {
    Relation newRelation(name, columnNames);
    for (Tuple t : tuples) {
        if (t.rowValues.at(columnIndex) == value) {
            newRelation.AddTuple(t);
        }
    }
    return newRelation;
}

Relation Relation::select2(unsigned int columnIndex1, unsigned int columnIndex2) {
    Relation newRelation(name, columnNames);
    for (Tuple t : tuples) {
        if (t.rowValues.at(columnIndex1) == t.rowValues.at(columnIndex2)) {
            newRelation.AddTuple(t);
        }
    }
    return newRelation;
}

Relation Relation::project(std::vector<unsigned int>& columnsToProject) {
    Header newHeader;
    for (auto & i : columnsToProject) {
        newHeader.addColumnName(columnNames.getColumn(i));
    }
    Relation newRelation(name, newHeader);
    for (Tuple t : tuples) {
        Tuple newTuple;
        for (auto & i : columnsToProject) {
            newTuple.addValue(t.rowValues.at(i));
        }
        newRelation.AddTuple(newTuple);
    }
    return newRelation;
}

Relation Relation::rename(std::vector<std::string>& newColumnNames) {
    Relation newRelation(name, Header(newColumnNames));
    newRelation.tuples = tuples;
    return newRelation;
}

Relation Relation::Join(Relation other) {
    std::map<unsigned int, unsigned int> sourceMap;
    std::vector<unsigned int> uniqueIndices;
    Header newHeader = combineHeaders(columnNames, other.columnNames, sourceMap, uniqueIndices);
    Relation newRelation(name, newHeader);
    for (Tuple i : tuples) {
        for (Tuple j : other.tuples) {
            if (isJoinable(i, j, sourceMap)) {
                newRelation.AddTuple(combineTuples(i, j, uniqueIndices));
            }
        }
    }
    return newRelation;
}

Header Relation::combineHeaders(Header& header1, Header& header2, std::map<unsigned int, unsigned int>& sourceMap, std::vector<unsigned int>& uniqueIndices) {
    Header newHeader;
    for (unsigned int i = 0; i < header1.getSize(); i++) {
        newHeader.addColumnName(header1.getColumn(i));
        for (unsigned int j = 0; j < header2.getSize(); j++) {
            if (header1.getColumn(i) == header2.getColumn(j)) {
                sourceMap[i] = j;
            }
        }
    }
    for (unsigned int i = 0; i < header2.getSize(); i++) {
        bool isUnique = true;
        std::map<unsigned int, unsigned int>::iterator it;
        for (it = sourceMap.begin(); it != sourceMap.end(); it++) {
            if (i == it->second) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            uniqueIndices.push_back(i);
        }
    }
    for (auto & uniqueIndex : uniqueIndices) {
        newHeader.addColumnName(header2.getColumn(uniqueIndex));
    }
    return newHeader;
}

bool Relation::isJoinable(Tuple& tuple1, Tuple& tuple2, std::map<unsigned int, unsigned int>& sourceMap) {
    std::map<unsigned int, unsigned int>::iterator it;
    for (it = sourceMap.begin(); it != sourceMap.end(); it++) {
        if (tuple1.rowValues.at(it->first) != tuple2.rowValues.at(it->second)) {
            return false;
        }
    }
    return true;
}

Tuple Relation::combineTuples(Tuple& tuple1, Tuple& tuple2, std::vector<unsigned int>& uniqueIndices) {
    Tuple newTuple;
    for (auto & rowValue : tuple1.rowValues) {
        newTuple.addValue(rowValue);
    }
    for (auto & uniqueIndex : uniqueIndices) {
        newTuple.addValue(tuple2.rowValues.at(uniqueIndex));
    }
    return newTuple;
}

std::string Relation::toString() {
    std::string output = "";
    for (Tuple t : tuples) {
        for (unsigned int i = 0; i < columnNames.getSize(); i++) {
            if (i == 0) {
                output += "  ";
            }
            output += columnNames.getColumn(i) + '=' + t.rowValues[i];
            if (i < columnNames.getSize() - 1) {
                output += ", ";
            } else {
                output += '\n';
            }
        }
    }
    return output;
}

std::string Relation::unionize(Relation other) {
    std::string output = "";
    for (Tuple t : other.tuples) {
        if (tuples.find(t) == tuples.end()) {
            AddTuple(t);
            output += "  ";
            for (unsigned int i = 0; i < columnNames.getSize(); i++) {
                output += columnNames.getColumn(i) + "=" + t.rowValues.at(i);
                if (i < columnNames.getSize() - 1) {
                    output += ", ";
                }
            }
            output += "\n";
        }
    }
    return output;
}
