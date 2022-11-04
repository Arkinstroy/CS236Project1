#ifndef DATABASE_H
#define DATABASE_H

#include "Relation.h"
#include <map>
#include <string>

class Database {
private:
    std::map<std::string, Relation> database;
public:
    void AddRelation(Relation* newRelation);
    Relation* GetRelation(std::string relationName);
    Relation GetRelationCopy(std::string relationName);
};


#endif // DATABASE_H
