//
// Created by Brady Sillito on 2021-10-28.
//

#ifndef HEADER_H
#define HEADER_H
#include <vector>
#include <string>
#include <iostream>
#include "Token.h"

class Header {
private:
    std::vector<std::string> attributes;
public:
    Header(std::vector<std::string> attributes);
    Header(){};

    void toString();
    void toString(int i);
    unsigned int size();
    void rename(unsigned int i,std::string variable);
    void projectHeader(unsigned int i);
    bool checkSelect(std::string varCheck);
    int matchIndex(std::string varCheck);
    std::vector<std::string> getAttributes();

};


#endif //HEADER_H
