#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <vector>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:

    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;

    void CreateAutomata();

    // TODO: add any other private methods here (if needed)

public:
    Lexer(std::string inFile);
    ~Lexer();


    void Run(std::string& input);

    
    // TODO: add other public methods here

};

#endif // LEXER_H

