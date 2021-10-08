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
public:
    Parameter(Token* token);
    Parameter(){};

    void setParameter(Token* token);
    void toString();
    std::string getString();
};


#endif //PROJECT1_STARTER_CODE_PARAMETER_H
