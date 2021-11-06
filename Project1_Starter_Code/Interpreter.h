//
// Created by Brady Sillito on 2021-10-31.
//

#ifndef PROJECT1_STARTER_CODE_INTERPRETER_H
#define PROJECT1_STARTER_CODE_INTERPRETER_H

#include "DatalogProgram.h"
#include <iostream>
#include "Header.h"
#include "Tuple.h"
#include "Relation.h"
#include "Predicate.h"
#include "DataBase.h"

class Interpreter {
public:
    Interpreter(DatalogProgram *dataLog);
    ~Interpreter(){};

    void build();
    Relation* evaluatePredicate(Predicate* query);
    void evaluatePredicate(std::vector<Predicate *> queries);

private:
    DatalogProgram *data;
    DataBase* dataBase;

    Header *tempHeader;
    Tuple tempTuple;
    std::vector<Relation*> relations;
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;

    void buildRelation();
    void buildTuples();
    void toString();
};


#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
