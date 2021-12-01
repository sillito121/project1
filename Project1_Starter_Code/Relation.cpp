//
// Created by Brady Sillito on 2021-10-28.
//

#include "Relation.h"

Relation::Relation(Header *header, std::string name) {
    this->header=header;
    this->name=name;
}

void Relation::toString() {
    if(tuples.size()==0){
        std::cout<<" No"<<std::endl;
        return;
    }

    std::cout<<" Yes("<<tuples.size()<<")"<< std::endl;
    std::set<Tuple>::iterator setItr = tuples.begin();
    for (unsigned int i = 0; i < tuples.size(); i++){
        Tuple tempTuple = *setItr;
        if(tempTuple.valSize() == 0){
            return;
        }
        std::cout<<"  ";
        for (unsigned int j = 0; j < header->size(); j++){
            header->toString(j);
            std::cout<<"=";
            tempTuple.toString(j);
            if(j!=header->size()-1){
                std::cout<<", ";
            }
        }
        if(i!=tuples.size()-1) {
            setItr++;
        }
        std::cout<<std::endl;
    }
}

void Relation::Print() {


    std::set<Tuple>::iterator setItr = tuples.begin();
    for (unsigned int i = 0; i < tuples.size(); i++){
        Tuple tempTuple = *setItr;
        if(tempTuple.valSize() == 0){
            return;
        }
        std::cout<<"  ";
        for (unsigned int j = 0; j < header->size(); j++){
            header->toString(j);
            std::cout<<"=";
            tempTuple.toString(j);
            if(j!=header->size()-1){
                std::cout<<", ";
            }
        }
        if(i!=tuples.size()-1) {
            setItr++;
        }
        std::cout<<std::endl;
    }
}


std::string Relation::getName() {
    return name;
}

void Relation::setTuple(Tuple tuple) {
    tuples.insert(tuple);
}

void Relation::select(unsigned int i, std::string constant) {
    std::set<Tuple>::iterator itr= tuples.begin();


    while(itr != tuples.end()){
        Tuple temp = *itr;
        if(temp.getVal(i)!=constant){
            itr = tuples.erase(itr);
        }
        else{
            itr++;
        }
    }
}
void Relation::select(unsigned int i, unsigned int j, std::string variable) {
    std::set<Tuple>::iterator itr= tuples.begin();
    while(itr != tuples.end()){
        Tuple temp = *itr;
        if(temp.getVal(i)!=temp.getVal(j)){
            itr = tuples.erase(itr);
        }
        else{
            itr++;
        }
    }
    rename(i,variable); // here is the problem right here.
    project(i);
}
void Relation::rename(unsigned int i, std::string variable) {
    header->rename(i,variable);
}

void Relation::project(unsigned int i) {
    std::set<Tuple>::iterator itr= tuples.begin();
    std::set<Tuple> projectTuple;

    while(itr != tuples.end()){
        Tuple temp = *itr;
        temp.projectTuple(i);
        projectTuple.insert(temp);
        itr++;
    }
    tuples = projectTuple;
    header->projectHeader(i);
}

bool Relation::checkSelect(std::string varCheck) {
    bool equalVar= header->checkSelect(varCheck);
    return equalVar;
}

int Relation::matchIndex(std::string varCheck) {
    unsigned int index = header->matchIndex(varCheck);
    return index;
}

void Relation::projectVec(std::vector<int> markPlace, int deleter) {

    for(unsigned int i=0; i<markPlace.size();i++){
        //If place marked is a constant selct the columns of that constant.
        if(markPlace[i]!=0) {
            project(i-deleter);
        }
    }

}

std::set<Tuple> Relation::getAllTuples() {
    return tuples;
}

void Relation::setAllTuples(std::set<Tuple> tuples) {
    this->tuples=tuples;

}

void Relation::addTuples(std::set<Tuple> tuples) {
    std::set<Tuple>::iterator itr= tuples.begin();
    while(itr != tuples.end()){
        Tuple temp = *itr;
        this->tuples.insert(temp);
        itr++;
    }

}
Header *Relation::getHeader() {
    return header;
}

int Relation::tupleNum() {
    return tuples.size();
}

void Relation::setName(std::string name) {
    this->name=name;

}









