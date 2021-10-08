#ifndef PARSER_H
#define PARSER_H
#include "Token.h"
#include <iostream>
#include <vector>
#include "Predicate.h"
#include "Parameter.h"
#include "DatalogProgram.h"
#include "Rule.h"

class Parser
{
private:
    std::vector<Token*> parseTokens;
    int index;
    Predicate *tempPredicate;
    Rule* rule;
    DatalogProgram *dataLog;

    void parseDatalogProgram();
    void parseSchemeList();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();
    void parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();
    void parseHeadPredicate();
    void parsePredicate();
    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    void parseIdList();
    void parseParameter();

public:
    Parser(std::vector<Token*> tokens);
    ~Parser();

    void parse();
    //DatalogProgram parse();

};

#endif //PROJECT1_STARTER_CODE_PARSER_H
