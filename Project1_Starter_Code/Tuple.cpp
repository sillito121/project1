//
// Created by Brady Sillito on 2021-10-28.
//

#include "Tuple.h"

void Tuple::buildTuple(std::vector<std::string> values) {
    this->values=values;
}

void Tuple::toString() {
    std::cout<<"|";
    for(unsigned int i=0; i<values.size();i++){
        std::cout<<values[i]<<"|";
    }
    std::cout<<std::endl;

}


std::string Tuple::getVal(int i) {
    return values[i];
}

void Tuple::toString(int i) {
    std::cout << values[i];

}

void Tuple::projectTuple(int i) {
    values.erase(values.begin()+i);
}

unsigned int Tuple::valSize() {
    return values.size();
}

std::string Tuple::getString(int i) {
    return values[i];
}

std::vector<std::string> Tuple::getValues() {
    return values;
}

std::vector<std::string> Tuple::swap(unsigned int i, unsigned int j) {
    std::string temp;
    temp = values[i];
    values[i] = values[j];
    values[j] = temp;
    return values;
}
