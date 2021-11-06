//
// Created by Brady Sillito on 2021-10-07.
//

#ifndef PARAMETER_H
#define PARAMETER_H
#include <iostream>
#include <string>
#include "Token.h"


class Parameter {
private:
    std::string parameter;
    Token* token;
public:
    Parameter(Token* token);
    Parameter(){};

    void setParameter(Token* token);
    void toString();
    std::string getString();
    bool isConstant();

};


#endif //PARAMETER_H
