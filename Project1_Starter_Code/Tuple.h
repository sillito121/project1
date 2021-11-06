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
    void toString(int i);
    void project(int i);
};


#endif //TUPLE_H
