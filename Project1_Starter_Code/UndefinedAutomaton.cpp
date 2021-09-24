#include "UndefinedAutomaton.h"

void UndefinedAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);

    } else if(input[index]=='\''){
        inputRead++;
        index++;
        S3(input);
    }
    else {
        Serr();
    }
}
void UndefinedAutomaton::S1(const std::string& input){
    if(input[index] =='|'){
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

void UndefinedAutomaton::S2(const std::string& input){
    bool undefined = false;
    while (!undefined && index < input.size()){
        if(input[index] == ('|')){
            if(input[index+1] == '#'){
                undefined = true;
            }
        }
        if(input[index]=='\n'){
            newLines++;
        }
        if(!undefined){
            inputRead++;
            index++;
        }
    }
    if(undefined){
        ++inputRead;
    }

}

void UndefinedAutomaton::S3(const std::string& input){
    bool defined = false;
    while (!defined && index < input.size()){
        if(input[index]=='\n'){
            newLines++;
        }
        if(input[index] == ('\'')){
            defined = true;
            if(input[index+1] == '\''){
                defined = false;
                inputRead++;
                index++;
            }
        }
        if(!defined){
            inputRead++;
            index++;
        }
    }
    if(defined){
        ++inputRead;
    }


}

