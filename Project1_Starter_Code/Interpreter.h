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
#include "Rule.h"
#include "DataBase.h"

class Interpreter {
public:
    Interpreter(DatalogProgram *dataLog);
    ~Interpreter(){};

    void build();
    Relation* evaluatePredicate(Predicate* pred);
    void evaluatePredicate(std::vector<Predicate *> pred);
    Relation * evaluateRule(Rule* rule);
    void evaluateRules(std::vector<Rule*> ruleVec);


private:
    DatalogProgram *data;
    DataBase* dataBase;
    Tuple tempTuple;
    std::vector<Relation*> relations;
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Rule*> rules;

    void buildRelation();
    void buildTuples();
    void toString();
    Relation * naturalJoin(Rule* r);
    Relation *join(Relation *body1, Relation *body2, std::string name);
    static Tuple combineTuple(Tuple tupOne, Tuple tupTwo, std::vector<unsigned int> deleteIndex);
    Tuple combineTuple(Tuple tuple1, Tuple tuple2);
    Header* combineHeader(Relation* body1, Relation* body2);
    Relation * matchHeadPred(Relation *finalBody, Predicate *headPred);
    Relation *crossProduct(Relation *body1, Relation *body2, std::string name);
    static Relation* reOrder(Relation* relate, std::vector<std::string> headArg);



};


#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
