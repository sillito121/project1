
#include "DatalogProgram.h"
#include <algorithm>

void DatalogProgram::buildSchemes(Predicate *predicate) {
    schemes.push_back(predicate);
}

void DatalogProgram::buildFacts(Predicate *predicate) {
    facts.push_back(predicate);
}

void DatalogProgram::buildQueries(Predicate *predicate) {
    queries.push_back(predicate);
}


void DatalogProgram::buildRules(Rule *rule) {
    rules.push_back(rule);
}

void DatalogProgram::toString() {
    std::cout<<"Schemes("<<schemes.size()<<"):"<<std::endl;
    for(unsigned int i=0; i<schemes.size();i++){
        std::cout <<"  ";
        schemes[i]->toString();
        std::cout<<std::endl;
    }

    std::cout<<"Facts("<<facts.size()<<"):"<<std::endl;
    for(unsigned int i=0; i<facts.size();i++){
        std::cout <<"  ";
        facts[i]->toString();
        std::cout<<"."<<std::endl;
    }

    std::cout<<"Rules("<<rules.size()<<"):"<<std::endl;
    for(unsigned int i=0; i<rules.size();i++){
        std::cout <<"  ";
        rules[i]->toString();
        std::cout<<"."<<std::endl;
    }

    std::cout<<"Queries("<<queries.size()<<"):"<<std::endl;
    for(unsigned int i=0; i<queries.size();i++){
        std::cout <<"  ";
        queries[i]->toString();
        std::cout<<"?"<<std::endl;
    }

    //Find the Domain size
    sortFacts();
    std::cout<<"Domain("<< domain.size()<<"):"<<std::endl;
    for(unsigned int i=0; i<domain.size();i++){
        std::cout<<"  "<<domain[i]<<std::endl;
    }
}

void DatalogProgram::sortFacts() {
    for(unsigned int i=0; i<facts.size();i++){
        makeDomain(facts[i]);
    }

    std::sort(domain.begin(),domain.end());


    for(unsigned int i=0; i<domain.size();i++){
        if(domain[i]==domain[i+1]){
            domain.erase(domain.begin()+i, domain.begin()+(i+1));
            i--;
        }
    }

}

void DatalogProgram::makeDomain(Predicate* fact) {
    std::vector<std::string> partDom = fact->getString();
    for(unsigned int i=0; i<partDom.size();i++){
        domain.push_back(partDom[i]);
    }
}

std::vector<Predicate *> DatalogProgram::getSchemes() {
    return schemes;
}

std::vector<Predicate *> DatalogProgram::getFacts() {
    return facts;
}

std::vector<Predicate *> DatalogProgram::getQueries() {
    return queries;
}



