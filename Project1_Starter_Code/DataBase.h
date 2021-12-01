//
// Created by Brady Sillito on 2021-10-31.
//

#ifndef DATABASE_H
#define DATABASE_H

#include "DatalogProgram.h"
#include "Relation.h"
#include <map>
#include <iostream>

class DataBase {
private:
    std::map<std::string,Relation*> dataMap;
public:

    DataBase(std::vector<Relation*> relation);
    ~DataBase(){};

    void fillMap(std::string name, Relation* relation);
    void toString();
    void toString(std::string name);
    Relation* find(std::string name);
    void addTuplesTo(std::set<Tuple> tuples, std::string name);
    std::vector<std::string> getHeader(std::string name);
    std::set<Tuple> unique(std::set<Tuple> tuples, std::string name);

};


#endif //DATABASE_H
