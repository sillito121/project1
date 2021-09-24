#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "Q_MarkAutomaton.h"
#include "Left_ParenAutomaton.h"
#include "Right_ParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "QueriesAutomaton.h"
#include "RulesAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "LComAutomaton.h"


Lexer::Lexer(std::string inFile) {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new Q_MarkAutomaton());
    automata.push_back(new Left_ParenAutomaton());
    automata.push_back(new Right_ParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new LComAutomaton());

    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;
    while (0<input.size()){
        int maxRead=0;
        Automaton *maxAutomaton = automata[0];

        while(std::isspace(input[0])){
            if(input[0]=='\n'){
                lineNumber++;
            }
            input.erase(0,1);
        }
        // Here is the "Parallel" part of the algorithm
        for(unsigned int i=0; i<automata.size(); ++i){ //*automata de-reference?
            int inputRead = automata[i]->Start(input);
            if(inputRead>maxRead){
                maxRead = inputRead;
                maxAutomaton = automata[i];
            }
        }
        if(maxRead>0){
            //assign the max automata to newToken
            Token *newToken = maxAutomaton->CreateToken(input.substr(0,maxRead),lineNumber);
            tokens.push_back(newToken);
            lineNumber += maxAutomaton->NewLinesRead();
        }else if(maxRead==0 && input.size()!=0){
            maxRead=1;
            Token *newToken = new Token(TokenType::UNDEFINED,input.substr(0,maxRead),lineNumber);
            tokens.push_back(newToken);
        }

        if(input.size()!=0){
            input.erase(0,maxRead);
        }
    }


    Token *eofToken = new Token(TokenType::EOF_FILE,"", lineNumber);
    tokens.push_back(eofToken);

    for(unsigned int i=0;i<tokens.size();i++){
        tokens[i]->toString();
    }
    std::cout<<"Total Tokens = "<< tokens.size();

}


