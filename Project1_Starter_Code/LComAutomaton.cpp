#include "LComAutomaton.h"
#include <iostream>
#include <sstream>


void LComAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        index++;
        S1(input);
        S2(input);
    }
    else {
        Serr();
    }
}

void LComAutomaton::S1(const std::string& input) {
    if(input[index] != '|'){
        std::istringstream f(input);
        std::string getIt;
        std::getline(f,getIt);

        if(getIt[getIt.size()-1] == '\r'){
            getIt.erase(getIt.size()-1);
        }
        inputRead = getIt.size();
    }
    else {
        Serr();
    }
}
void LComAutomaton::S2(const std::string& input){
    if(input[index]=='|'){
        index++;
        inputRead++;
        S3(input);
    }
}

void LComAutomaton::S3(const std::string& input){
    if(input.size() == index) {
        type = TokenType::UNDEFINED;
    }else if(input[index]!= '|' && index!=input.size()){
        if(input[index]=='\n'){
            newLines++;
        }
        index++;
        inputRead++;
        S3(input);
    } else if (input[index] == '|'){
        if(input[index+1] == '#'){
            inputRead+=2;
        } else if (input[index+1]!=EOF && input[index+1] != '#'){
            inputRead++;
            index++;
            S3(input);
        }
    }
    else{
        Serr();
    }
}





