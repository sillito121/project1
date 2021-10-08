//
// Created by Brady Sillito on 2021-10-07.
//

#ifndef RULE_H
#define RULE_H
#include <string>
#include <vector>
#include "Predicate.h"


class Rule {
private:
    Predicate* headPredicate;
    std::vector<Predicate*> predicates;

public:
    void toString();
    void pushParam(Predicate* predicate);
    void setHead(Predicate* predicate);

};


#endif //PROJECT1_STARTER_CODE_RULE_H
