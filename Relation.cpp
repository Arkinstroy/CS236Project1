#include "Relation.h"

#include <string>

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
        for (int i : columnsToProject) {
            newTuple.addValue(t.rowValues[i]);
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
    return Relation();
}

std::string Relation::toString() {
    std::string output = "";
    for (Tuple t : tuples) {
        for (unsigned int i = 0; i < columnNames.getSize(); i++) {
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
