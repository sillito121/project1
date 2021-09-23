#include "Lexer.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {

    std::string filename = argv[1];
    std::ifstream file(filename);
    std::string inputFile;
    if(!file.is_open()){
        std::cout<<"failed to open"<<std::endl;
    } else {
        while(file.peek() != EOF){
            inputFile += file.get();
        }
    }
    Lexer* lexer = new Lexer(inputFile);
    lexer->Run(inputFile);
    delete lexer;
    return 0;
}