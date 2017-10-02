#ifndef NUMBER_H
#define NUMBER_H

#include <string>
using std::string;
class Variable ;
class Atom ;
class Number{
public:
    Number (string init_string):_string(init_string),_value(init_string){}
    string symbol(){ return _string; }
    string value (){ return _value; }   
    bool match( string matchValue);
    bool match ( Variable &var);
    bool match ( Atom &atom);
    bool match ( Number &num);
private:
    string _string="" ;
    string _value="0";  
    bool _assignable = true;
};
#endif