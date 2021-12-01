//
// Created by Brady Sillito on 2021-10-07.
//

#include "Rule.h"

void Rule::pushParam(Predicate* predicate){
    predicates.push_back(predicate);
}

void Rule::setHead(Predicate* predicate){
    headPredicate = predicate;
}

void Rule::toString() {
    headPredicate->toString();
    std::cout<<" :- ";
    for(unsigned int i=0; i<predicates.size();i++){
        predicates[i]->toString();
        if(i!=predicates.size()-1){
            std::cout<<",";
        } else{
            std::cout<<".";
        }
    }
}

std::vector<Predicate *> Rule::getBody() {
    return predicates;
}

Predicate *Rule::getHead() {
    return headPredicate;
}
