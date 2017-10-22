#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include <iostream>
#include "atom.h"
#include "struct.h"

using std::string;
using namespace std;

class Variable : public Term{
public:
  Variable(string s):_symbol(s),_value(s){ string* val = &_value; val_ptr = val;  (*community).push_back(this); }
  string  symbol() const{
    return _symbol;
  }
  string value() const {
    if(tmpStr){
      *val_ptr = tmpStr->value();
    }
    return (*val_ptr) ;
  }

  bool match( Term &term ){
    bool ret_temp = this->_did_not_assign_the_class_before;
    Variable * match_Variable = dynamic_cast<Variable *> (&term) ;
    Struct * Match_Struct =dynamic_cast<Struct *> (&term);
    if(match_Variable){
      if(match_Variable->_did_not_assign_the_class_before){   
        community->push_back( match_Variable  );           
        match_Variable ->community = ( community) ;       
      ret_temp =true;
      }      
      else if(( ((*match_Variable).value()) == value())) {
        ret_temp = true;
      }
      else{
        if(this->_did_not_assign_the_class_before){
          val_ptr = match_Variable->val_ptr;
          this->_did_not_assign_the_class_before = false;
          ret_temp  = true;           
        }
        else
          ret_temp  =false;
      }
    }  
    else if(Match_Struct){
      if(this->_did_not_assign_the_class_before){
        *val_ptr = Match_Struct->value();
        tmpStr = Match_Struct ;
        for(int i = 0; i < community->size()  ; i++){
          if( ((*community)[i])->val_ptr != val_ptr ){
            (*community)[i]->val_ptr = val_ptr;            
          }
        }  
        this->_did_not_assign_the_class_before = false;
      }
    }
    else{
      if(this->_did_not_assign_the_class_before){
        *val_ptr = term.value();
        for(int i = 0; i < community->size()  ; i++){
          if( ((*community)[i])->val_ptr != val_ptr ){
            (*community)[i]->val_ptr = val_ptr;            
          }
        }  
        this->_did_not_assign_the_class_before = false;

      }
      else if(*val_ptr == term.symbol()){        
        ret_temp = true;
      }
      
    }
    
    return ret_temp;
  }
  
protected:
  bool _did_not_assign_the_class_before = true;
  Struct *tmpStr = NULL;
  string *val_ptr= NULL;  
  std::vector <Variable *> *community = new std::vector<Variable*>();
  
private:
  string _symbol;
  string _value;

};


#endif
