//
// Created by Brady Sillito on 2021-10-07.
//

#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include <string>
#include <vector>
#include "Predicate.h"
#include "Rule.h"


class DatalogProgram {
public:
    void toString();
    void buildSchemes(Predicate* predicate);
    void buildFacts(Predicate* predicate);
    void buildQueries(Predicate* predicate);
    void buildRules(Rule* rule);


private:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;
    std::vector<std::string> domain;
    void makeDomain(Predicate* fact);
    void sortFacts();

};


#endif //PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
