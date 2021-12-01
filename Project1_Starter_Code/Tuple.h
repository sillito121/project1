#ifndef TUPLE_H
#define TUPLE_H
#include <vector>
#include <string>
#include <iostream>

class Tuple {
private:
    std::vector<std::string> values;


public:
    void buildTuple(std::vector<std::string> values);
    void toString();
    std::string getVal(int i);
    bool operator< (const Tuple &rhs) const{
        return values < rhs.values;
    }
    unsigned int valSize();
    void toString(int i);
    void projectTuple(int i);
    std::string getString(int i);
    std::vector<std::string> getValues();
};


#endif //TUPLE_H
