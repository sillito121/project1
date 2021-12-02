//
// Created by Brady Sillito on 2021-10-28.
//

#ifndef RELATION_H
#define RELATION_H
#include <set>
#include "Tuple.h"
#include "Header.h"
#include "Predicate.h"


class Relation {
private:
    std::set<Tuple> tuples;
    std::string name;
    Header *header;



public:
    Relation(Header* header, std::string name);
    ~Relation(){};

    void toString();
    void Print();
    std::string getName();
    void setName(std::string name);
    Header* getHeader();
    std::set<Tuple> getAllTuples();
    void setAllTuples(std::set<Tuple> tuples);
    void setTuple(Tuple tuple);
    void addTuples(std::set<Tuple> tuples);
    void select(unsigned int i, std::string constant);
    void select(unsigned int i, unsigned int j, std::string variable);
    void rename(unsigned int i, std::string variable);
    void project(unsigned int i);
    void projectVec(std::vector<int> markPlace, int deleter);
    bool checkSelect(std::string varCheck);
    int matchIndex(std::string varCheck);
    std::set<Tuple> getColumn(unsigned int i);


    int tupleNum();



};


#endif //RELATION_H
