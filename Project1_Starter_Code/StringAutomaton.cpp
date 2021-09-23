#include "StringAutomaton.h"



void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if(input.size()==index){
        Serr();
    }else if((input[index] != '\'')&& index != input.size()){
        inputRead++;
        index++;
        if(input[index]=='\n'){
            newLines++;
        }
        S1(input);
    } else if (input[index] == '\''){
        inputRead++;
        if (input[index+1] == '\''){
            index+=2;
            inputRead++;
            S1(input);
        }
    }
    else {
        Serr();
    }
}