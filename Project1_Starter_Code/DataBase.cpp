//
// Created by Brady Sillito on 2021-10-31.
//

#include "DataBase.h"

DataBase::DataBase(std::vector<Relation*> relation) {
    for(unsigned int i=0; i<relation.size();i++){
        fillMap(relation[i]->getName(),relation[i]);
    }
}

void DataBase::fillMap(std::string name, Relation *relation) {
    dataMap.insert(std::pair<std::string,Relation*>(name,relation));
}

void DataBase::toString() {
    std::cout<<"Map Size: "<< dataMap.size()<<std::endl;
    std::map<std::string,Relation*>::iterator itr;
    for (itr = dataMap.begin(); itr != dataMap.end(); ++itr) {
        (itr->second)->toString();
    }
}

Relation* DataBase::find(std::string name) {
    auto itr = dataMap.find(name);
    Relation *find = itr->second;
    return find;
}


