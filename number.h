#ifndef NUMBER_H
#define NUMBER_H

#include <string>
using std::string;
class Variable ;
class Atom ;
class Number{
public:
    Number (int init_IntegerToString):_string(std::to_string(init_IntegerToString)),_value(std::to_string(init_IntegerToString)){}    
    Number (double init_doubleToString):_string(std::to_string(init_doubleToString)),_value(std::to_string(init_doubleToString)){}
    string symbol(){ return _string; }
    string value (){ return _value; } 
    bool match ( Variable &var);
    bool match ( Atom &atom);
    bool match ( Number &num);
private:
    string _string="" ;
    string _value="0";  
    bool _assignable = true;
};
#endif