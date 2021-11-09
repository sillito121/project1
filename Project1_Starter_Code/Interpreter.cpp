//
// Created by Brady Sillito on 2021-10-31.
//

#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram *dataLog) {
    data=dataLog;
}

void Interpreter::build() {
    //std::cout<<"Building DataBase:" <<std::endl;
    buildRelation();
    dataBase = new DataBase(relations);
    //dataBase->toString();
 //   std::vector<Predicate*> queries = data->getQueries();
//    evaluatePredicate(queries[0]);
}

void Interpreter::buildRelation() {
    schemes=data->getSchemes();
    for(unsigned int i=0; i<schemes.size();i++){
        Header* tempHeader = new Header(schemes[i]->getString());
        relations.push_back(new Relation(tempHeader,schemes[i]->getName()));
    }
    buildTuples();
}

void Interpreter::buildTuples() {
    facts = data->getFacts();
    for(unsigned int i=0; i<facts.size();i++){
        for(unsigned int j=0; j<relations.size();j++){
            if(facts[i]->getName()==relations[j]->getName()){
                tempTuple.buildTuple(facts[i]->getString());
                relations[j]->setTuple(tempTuple);
            }
        }
    }
}

void Interpreter::toString() {
    for(unsigned int i=0; i<relations.size();i++){
        relations[i]->toString();
    }
}

Relation* Interpreter::evaluatePredicate(Predicate *query) {
    Relation *findRelation = dataBase->find(query->getName());
    Header* header = new Header(findRelation->getHeader()->getAttributes());
    Relation *evalName = new Relation(header,findRelation->getName());
    evalName->setAllTuples(findRelation->getAllTuples());

    std::vector<Parameter*> parameters = query->getParameters();

    std::vector<int> markPlace;
    //mark constants and variables
    for(unsigned int i=0; i<parameters.size();i++){
        bool isConstant = parameters[i]->isConstant();
        if(isConstant){
            //if the parameter is a constant select its row
            evalName->select(i,parameters[i]->getString());
            markPlace.push_back(1);
        } else if(!isConstant){
            //if variable mark
            markPlace.push_back(0);
        }
    }
    // take care of variables
    int deleteIndex=0;
    for(unsigned int i=0; i<markPlace.size();i++){
        //If the marked place is a variable
        if(markPlace[i]==0){
            // Check if the current variable matches any past variables,
            if(evalName->checkSelect(parameters[i]->getString()) && (i != 0)){
                //Get the index of the Variable that it matches
                int index = evalName->matchIndex(parameters[i]->getString());
                //call select type 2 with the current and matching Variable
                evalName->select((i - deleteIndex), index, parameters[i]->getString());
                //markPlace.erase(markPlace.begin()+i);
                if( i != markPlace.size()-1){
                    deleteIndex++;
                }
            }else{
                int rVal = i-deleteIndex;
                evalName->rename(rVal, parameters[i]->getString());
            }
        }
    }
    //projectHeader remaining constants
    evalName->projectVec(markPlace, deleteIndex);
    return evalName;
}

void Interpreter::evaluatePredicate(std::vector<Predicate*> queries) {

    std::vector<Relation*> finalRel;
    for(unsigned int i=0; i<queries.size();i++){
        queries[i]->toString();
        std::cout<<"?";
        evaluatePredicate(queries[i])->toString();

    }
}
