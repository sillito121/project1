//
// Created by Brady Sillito on 2021-10-07.
//

#ifndef PREDICATE_H
#define PREDICATE_H
#include <string>
#include <vector>
#include "Token.h"
#include "Parameter.h"

class Predicate {
private:
    std::string name;
    std::vector<Parameter*> parameters;

public:
    Predicate(Token* token);
    Predicate(){};

    void toString();
    void setPredicate(Token* token);
    void fill(Token* token);
    unsigned int getSize();
    std::string getName();
    std::vector<std::string> getString();
    std::vector<Parameter*> getParameters();

};


#endif //PROJECT1_STARTER_CODE_PREDICATE_H
