#ifndef LCOMAUTOMATON_H
#define LCOMAUTOMATON_H

#include "Automaton.h"

class LComAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);


public:
    LComAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif

