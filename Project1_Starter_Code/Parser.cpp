#include "Parser.h"

Parser::Parser(std::vector<Token*> tokens) {
    index=0;
    parseTokens = tokens;
    for(unsigned int i=0;i<parseTokens.size();i++){
        if(parseTokens[i]->getType() == TokenType::COMMENT){
            delete parseTokens[i];
            parseTokens.erase(parseTokens.begin()+i);
            i--;
        }
    }
}

Parser::~Parser() {

}

void Parser::parse() {
    try {
        parseDatalogProgram();
    } catch (Token* error){
        std::cout<< "Failure!"<<std::endl;
        error->toString();
    }


}

void Parser::parseDatalogProgram() {
    dataLog = new DatalogProgram();
    if(parseTokens[index]->getType()==TokenType::SCHEMES){
        index++;
    } else {
        throw parseTokens[index];
    }
    if(parseTokens[index]->getType()==TokenType::COLON){
        index++;
        parseScheme();
        dataLog->buildSchemes(tempPredicate);
        parseSchemeList();
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::FACTS){
        index++;
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::COLON){
        index++;
        parseFactList();
    } else {
        throw parseTokens[index];
    }

    if(parseTokens[index]->getType()==TokenType::RULES){
        index++;
    } else {
        throw parseTokens[index];
    }

    if(parseTokens[index]->getType()==TokenType::COLON){
        index++;
        parseRuleList();
    } else {
        throw parseTokens[index];
    }

    if(parseTokens[index]->getType()==TokenType::QUERIES){
        index++;
    } else {
        throw parseTokens[index];
    }
    if(parseTokens[index]->getType()==TokenType::COLON){
        index++;
        parseQuery();
        dataLog->buildQueries(tempPredicate);
        parseQueryList();
    } else {
        throw parseTokens[index];
    }

    if(parseTokens[index]->getType()==TokenType::EOF_FILE){
        index++;
        Interpret();
        return;
    } else {throw parseTokens[index];}
}

void Parser::parseScheme() {
    if(parseTokens[index]->getType()==TokenType::ID){
        tempPredicate = new Predicate(parseTokens[index]);
        index++;
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::LEFT_PAREN){
        index++;
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::ID){
        tempPredicate->fill(parseTokens[index]);
        index++;
        parseIdList();
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::RIGHT_PAREN){
        index++;
        return;
    } else {throw parseTokens[index];}
}

void Parser::parseIdList() {
    if(parseTokens[index]->getType()==TokenType::COMMA){
        index++;
    } else {return;}

    if(parseTokens[index]->getType()==TokenType::ID){
        tempPredicate->fill(parseTokens[index]);
        index++;
        parseIdList();
    } else {throw parseTokens[index];}
}

void Parser::parseSchemeList() {
    if(parseTokens[index]->getType()==TokenType::ID){
        parseScheme();
        dataLog->buildSchemes(tempPredicate);
        parseSchemeList();
    } else {return;}
}

void Parser::parseFactList() {
    if(parseTokens[index]->getType()==TokenType::ID){
        parseFact();
        dataLog->buildFacts(tempPredicate);
        parseFactList();
    } else {return;}
}

void Parser::parseFact() {
    if(parseTokens[index]->getType()==TokenType::ID){
        tempPredicate = new Predicate(parseTokens[index]);
        index++;
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::LEFT_PAREN){
        index++;
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::STRING){
        tempPredicate->fill(parseTokens[index]);
        index++;
        parseStringList();
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::RIGHT_PAREN){
        index++;
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::PERIOD){
        index++;
    } else {throw parseTokens[index];}


}

void Parser::parseStringList() {
    if(parseTokens[index]->getType()==TokenType::COMMA){
        index++;
    } else {return;}

    if(parseTokens[index]->getType()==TokenType::STRING){
        tempPredicate->fill(parseTokens[index]);
        index++;
        parseStringList();
    } else {throw parseTokens[index];}
}

void Parser::parseRuleList() {
    if(parseTokens[index]->getType()==TokenType::ID){
        parseRule();
        dataLog->buildRules(rule);
        parseRuleList();
    } else {return;}
}

void Parser::parseRule() {
    if(parseTokens[index]->getType()==TokenType::ID){
        rule = new Rule();
        parseHeadPredicate();
        rule->setHead(tempPredicate);
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::COLON_DASH){
        index++;
        parsePredicate();
        rule->pushParam(tempPredicate);
        parsePredicateList();
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::PERIOD){
        index++;
    } else {throw parseTokens[index];}
}

void Parser::parseHeadPredicate() {
    if(parseTokens[index]->getType()==TokenType::ID){
        tempPredicate = new Predicate(parseTokens[index]);
        index++;
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::LEFT_PAREN){
        index++;
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::ID){
        tempPredicate->fill(parseTokens[index]);
        index++;
        parseIdList();
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::RIGHT_PAREN){
        index++;
    } else {throw parseTokens[index];}

}

void Parser::parsePredicate() {
    if(parseTokens[index]->getType()==TokenType::ID){
        tempPredicate = new Predicate(parseTokens[index]);
        index++;
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::LEFT_PAREN){
        index++;
        parseParameter();
        parseParameterList();
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::RIGHT_PAREN){
        index++;
    } else {throw parseTokens[index];}
}

void Parser::parseParameter() {
    if(parseTokens[index]->getType()==TokenType::STRING){
        tempPredicate->fill(parseTokens[index]);
        index++;
    } else if (parseTokens[index]->getType()==TokenType::ID) {
        tempPredicate->fill(parseTokens[index]);
        index++;
    } else{throw parseTokens[index];}
}

void Parser::parseParameterList() {
    if(parseTokens[index]->getType()==TokenType::COMMA){
        index++;
        parseParameter();
        parseParameterList();
    } else {return;}
}

void Parser::parsePredicateList() {
    if(parseTokens[index]->getType()==TokenType::COMMA){
        index++;
        parsePredicate();
        rule->pushParam(tempPredicate);
        parsePredicateList();
    } else {return;}

}

void Parser::parseQuery() {
    if(parseTokens[index]->getType()==TokenType::ID){
        tempPredicate = new Predicate(parseTokens[index]);
        parsePredicate();
    } else {throw parseTokens[index];}

    if(parseTokens[index]->getType()==TokenType::Q_MARK){
        index++;
    } else {throw parseTokens[index];}

}

void Parser::parseQueryList() {
    if(parseTokens[index]->getType()==TokenType::ID){
        parseQuery();
        dataLog->buildQueries(tempPredicate);
        parseQueryList();
    } else {return;}

}

void Parser::Interpret() {
    Interpreter* interpreter = new Interpreter(dataLog);
    interpreter->build();
    std::vector<Rule*> rules = dataLog->getRules();
    interpreter->evaluateRules(rules);
    interpreter->evaluatePredicate(dataLog->getQueries());

}

