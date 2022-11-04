#include "Database.h"


void Database::AddRelation(Relation* newRelation) {
    database[newRelation->GetName()] = *newRelation;
}

Relation *Database::GetRelation(std::string relationName) {
    return &database[relationName];
}

Relation Database::GetRelationCopy(std::string relationName) {
    return database[relationName];
}
