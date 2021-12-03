#include "Header.h"

Header::Header(std::vector<std::string> attributes) {
    this->attributes=attributes;
}

void Header::toString(){
    std::cout<<"|";
    for(unsigned int i=0;i<attributes.size();i++){
        std::cout<< attributes[i]<<"|";
    }
    std::cout<<std::endl;

}

void Header::toString(int i) {
    std::cout<<attributes[i];

}

unsigned int Header::size() {
    return attributes.size();
}

void Header::rename(unsigned int i, std::string variable) {
    attributes[i]=variable;
}

void Header::projectHeader(unsigned int i) {
    attributes.erase(attributes.begin()+i);
}

bool Header::checkSelect(std::string varCheck) {
    bool varEqual = false;
    for(unsigned int i=0;i<attributes.size();i++){
        if(varCheck==attributes[i]){
            varEqual= true;
        }
    }
    return varEqual;
}

int Header::matchIndex(std::string varCheck) {
    for(unsigned int i=0;i<attributes.size();i++){
        if(varCheck==attributes[i]){
            unsigned int index = i;
            return index;
        }
    }
    return 0;
}

std::vector<std::string> Header::getAttributes() {
    return attributes;
}

void Header::rename(std::vector<std::string> attributes) {
    if(attributes.size() != this->attributes.size()){
        for(unsigned int i=0;i< this->attributes.size();i++){
            this->attributes[i]=attributes[i];
        }
    }else{
        this->attributes = attributes;
    }

}

void Header::swap(int i, int j) {
    std::string temp = attributes[i];
    attributes[i] = attributes[j];
    attributes[j] = temp;
}


