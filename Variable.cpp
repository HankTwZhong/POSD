#include "number.h"
#include "variable.h"
#include "atom.h"

string Variable::value(){ return this->_value; }
bool Variable::match(Atom &atom){
  bool ret_temp = this->_assignable;
  if( this->_assignable){
    this->_value = atom._symbol ;
    this->_assignable = false;
  }
  else if(this->_value == atom._symbol){
    return true;
  }
  return ret_temp;
}
bool Variable::match(Number &num ){
  bool ret_temp = this->_assignable;
  if(this->_assignable){
    this->_value = num.value();
    _assignable=false;
  }
  return ret_temp;
}

