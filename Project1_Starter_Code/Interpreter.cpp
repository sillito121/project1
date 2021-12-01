//
// Created by Brady Sillito on 2021-10-31.
//

#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram *dataLog) {
    data=dataLog;
}

void Interpreter::build() {
    buildRelation();
    dataBase = new DataBase(relations);
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

Relation* Interpreter::evaluatePredicate(Predicate *pred) {
    Relation *findRelation = dataBase->find(pred->getName());
    Header* header = new Header(findRelation->getHeader()->getAttributes());
    Relation *evalName = new Relation(header,findRelation->getName());
    evalName->setAllTuples(findRelation->getAllTuples());

    std::vector<Parameter*> parameters = pred->getParameters();

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

void Interpreter::evaluatePredicate(std::vector<Predicate*> predicates) {

    std::cout<<std::endl<<"Query Evaluation"<<std::endl;
    for(unsigned int i=0; i<predicates.size();i++){
        predicates[i]->toString();
        std::cout<<"?";
        evaluatePredicate(predicates[i])->toString();

    }
}

Relation * Interpreter::evaluateRule(Rule *rule) {
    std::cout<<std::endl;
    Relation* newRelate;
    if(rule->getBody().size()==1) {
        newRelate = matchHeadPred(evaluatePredicate(rule->getBody()[0]),rule->getHead());
    }else {
        newRelate= naturalJoin(rule);
    }

    std::set<Tuple> tuples = dataBase->unique(newRelate->getAllTuples(),newRelate->getName());

    newRelate->setAllTuples(tuples);

    dataBase->addTuplesTo(newRelate->getAllTuples(), rule->getHead()->getName());


    return newRelate;
}

void Interpreter::evaluateRules(std::vector<Rule *> ruleVec) {
    std::cout<<"Rule Evaluation"<<std::endl;
    bool emptySet = true;
    Relation* relate;
    int j =0;
    while (emptySet){
        emptySet = false;
        for(unsigned int i=0;i<ruleVec.size();i++){
            ruleVec[i]->toString();
            relate = evaluateRule(ruleVec[i]);
            relate->Print();
            if(!relate->getAllTuples().empty()){
                emptySet = true;
            }
        }
        j++;
    }

    std::cout<<std::endl<<"Schemes populated after "<<j<<" passes through the Rules."<<std::endl;


}

Relation * Interpreter::naturalJoin(Rule* r) {
    std:: vector<Predicate*>rules=r->getBody();

    if(r->getBody().size() == 2){
        Relation* finalBody = join(evaluatePredicate(rules[0]),evaluatePredicate(rules[1]));
        finalBody = matchHeadPred(finalBody, r->getHead());
        //dataBase->addTuplesTo(finalBody->getAllTuples(), r->getHead()->getName());
        return finalBody;
    } else{
        Relation* body1 = evaluatePredicate(rules[0]);
        int i = 0;

        while(!body1->getAllTuples().empty()){
            r->toString();
            Relation* finalBody = join(body1,evaluatePredicate(rules[i+1]));
            finalBody = matchHeadPred(finalBody, r->getHead());
            body1 = finalBody;
            i++;
        }

        return body1;
    }
}

Relation *Interpreter::join(Relation *body1, Relation *body2) {

    std::vector<int> alpha;
    std::vector<int> beta;

    for(unsigned int i=0; i<body1->getHeader()->getAttributes().size();i++){
        for(unsigned int j=0; j<body2->getHeader()->getAttributes().size();j++){
            if(body1->getHeader()->getAttributes()[i] == body2->getHeader()->getAttributes()[j]){
                alpha.push_back(i);
                beta.push_back(j);
            }
        }
    }

    //combine the headers and create new relation to return
    Relation* newRelate = new Relation(combineHeader(body1,body2),"new");
    std::set<Tuple> newTuple;

    if(alpha.empty()){
        //crossProduct
        return crossProduct(body1,body2);
    }

    //find tuples that have matching indexes
    for(Tuple tupBody1: body1->getAllTuples()){
        for(Tuple tupBody2: body2->getAllTuples()){
            int matches = 0;
            for(unsigned int i=0; i<alpha.size();i++){
                if(tupBody1.getString(alpha[i]) == tupBody2.getString(beta[i])){
                    matches++;
                }
            }
            if(matches==alpha.size()){
                //combine tuples function
                newTuple.insert(combineTuple(tupBody1,tupBody2,beta));
            }
        }
    }
    newRelate->setAllTuples(newTuple);
    return newRelate;
}

Header *Interpreter::combineHeader(Relation *body1, Relation* body2) {
    //add elements from first, get unique from second
    std::vector<std::string> headMaker = body1->getHeader()->getAttributes();

    // check for unique elements
    for(unsigned int i=0; i<body2->getHeader()->getAttributes().size();i++){
        bool unique = true;
        for(unsigned int j=0; j<headMaker.size();j++){
            if(headMaker[j] == body2->getHeader()->getAttributes()[i]){
                unique = false;
            }
        }
        if(unique){
            headMaker.push_back(body2->getHeader()->getAttributes()[i]);
        }
    }

    Header* header = new Header(headMaker);
    return header;
}

Tuple Interpreter::combineTuple(Tuple tupOne, Tuple tupTwo, std::vector<int> deleteIndex) {
    std::vector<std::string> tupleMaker1 = tupOne.getValues();
    std::vector<std::string> tupleMaker2 = tupTwo.getValues();
    for(int i=deleteIndex.size()-1; i>=0;i--){
        tupleMaker2.erase(tupleMaker2.begin()+deleteIndex[i]);
    }

    tupleMaker1.insert(tupleMaker1.end(),tupleMaker2.begin(),tupleMaker2.end());
    Tuple newTup;
    newTup.buildTuple(tupleMaker1);

    return newTup;
}

Tuple Interpreter::combineTuple(Tuple tuple1, Tuple tuple2) {
    std::vector<std::string> tupleMaker1 = tuple1.getValues();
    std::vector<std::string> tupleMaker2 = tuple2.getValues();
    tupleMaker1.insert(tupleMaker1.end(),tupleMaker2.begin(),tupleMaker2.end());
    Tuple newTup;
    newTup.buildTuple(tupleMaker1);

    return newTup;
}

Relation * Interpreter::matchHeadPred(Relation *finalBody, Predicate *headPred) {
    //we need to preform a select on the attributes of finalBody so they match with head Pred
    /* relation header and compare it against the attibutes of headPred
     * if the header does not match any of the attributes delete that header and tuples at that index*/
    if(finalBody->getHeader()->size() < headPred->getSize()){
        return finalBody;
    }

    for(unsigned int i=0; i<finalBody->getHeader()->size();i++){
        bool match = false;
        for(unsigned int j=0; j<headPred->getSize();j++){
            if(headPred->getString()[j] == finalBody->getHeader()->getAttributes()[i]) {
                match = true;
            }
        }
        if(!match){
            finalBody->project(i);
            i--;
        }
    }
    //dataBase->getHeader(headPred->getName());
    //check
    finalBody->getHeader()->rename(dataBase->getHeader(headPred->getName()));
    finalBody->setName(headPred->getName());



    return finalBody;
}

Relation *Interpreter::crossProduct(Relation *body1, Relation *body2) {
    Relation* crossP = new Relation(combineHeader(body1,body2),"new");

    for(Tuple combTuple1: body1->getAllTuples()){
        for(Tuple combTuple2: body2->getAllTuples()){
            crossP->setTuple(combineTuple(combTuple1,combTuple2));
        }
    }
    return crossP;
}


