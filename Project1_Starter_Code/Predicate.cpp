//
// Created by Brady Sillito on 2021-10-07.
//

#include "Predicate.h"

Predicate::Predicate(Token* token) {
    setPredicate(token);

}

void Predicate::setPredicate(Token* token) {
    std::string name = token->getDescrip();
    this->name = name;
}

void Predicate::fill(Token* token) {
    Parameter* p = new Parameter(token);
    parameters.push_back(p);
}

void Predicate::toString() {
    std::cout<<name<<"(";
    for(unsigned int i=0; i<parameters.size();i++){
        if(i != parameters.size()-1){
            parameters[i]->toString();
            std::cout<<",";
        } else{
            parameters[i]->toString();
        }

    }
    std::cout<<")";

}

unsigned int Predicate::getSize() {
    return parameters.size();
}

std::vector<std::string> Predicate::getString() {
    std::vector<std::string> stringList;
    for(unsigned int i=0; i<parameters.size();i++){
        stringList.push_back(parameters[i]->getString());
    }

    return stringList;
}

std::string Predicate::getName() {
    return name;
}

std::vector<Parameter *> Predicate::getParameters() {
    return parameters;
}


