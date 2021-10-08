#include "Parameter.h"

Parameter::Parameter(Token *token) {
    setParameter(token);
}

void Parameter::setParameter(Token* token) {
    std::string parameter = token->getDescrip();
    this->parameter=parameter;
}

void Parameter::toString() {
    std::cout<<parameter;
}

std::string Parameter::getString() {
    return parameter;
}
