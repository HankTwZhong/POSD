#include "number.h"
#include "variable.h"
#include "atom.h"

bool Number::match( string matchValue){
    if(matchValue == this->value() ){
        this->_assignable = true;
    }
    else{
        this->_assignable = false;
    }
    return this->_assignable;
}
bool Number::match ( Variable &var){
    Number thisNum = *this;
    return var.match(thisNum);     
}
bool Number::match (Atom &atom){
    return false;
}
bool Number::match(Number &num){
    if(num.value() == this->value()){
        this->_assignable =true;
    }
    else{
        this->_assignable =false;
    }
    return this->_assignable;
}