#ifndef LIST_H
#define LIST_H

#include "term.h"
#include "variable.h"
#include <vector>
#include <string>
#include <typeinfo>
#include <iostream>
using std::vector;

class List : public Term {
public:
  string symbol() const{
    string ret ;
    if(_elements.size()==0 ){
      ret = "[]";
    }
    else{
      ret  = "[";
      std::vector<Term *>::const_iterator it = _elements.begin();
      for( ; it != _elements.end()-1 ; ++it ){
        ret += (*it)->symbol()+",";
      }
      ret += (*it)->symbol()+"]";
    }
    return ret;
  }
  string value() const{
    string ret ;
    if(_elements.size()==0 ){
      ret = "[]";
    }
    else{
      // std::cout << "跑回圈" << std::endl;
      ret  = "[";
      std::vector<Term *>::const_iterator it = _elements.begin();
      for( ; it != _elements.end()-1 ; ++it ){
        ret += (*it)->value()+",";
      }
      ret += (*it)->value()+"]";
    }
    return ret;
  }
  bool match(Term & term) {
    std::cout << "list_list_finish" << std::endl;
    
    if(typeid(term) ==  typeid(List)){
      bool ret =true;      
      List * ptrls = dynamic_cast<List*>(&term);
      if( _elements.size() != ptrls->_elements.size() ){
        ret = false;
      }
      else{
        for(int i = 0 ; i < _elements.size() ;i++ ){
            ret = _elements[i]->match(*(ptrls->_elements[i])) ;
            if(ret == false)
              return ret;          
        }    
      }
      return ret;
    }
    else if(typeid(term) == typeid(Variable)){
      std::cout << "list_variable_finish" << std::endl;
      
      bool ret =true;            
      for(int i = 0 ; i < _elements.size() ;i++ ){
        if(typeid(_elements[i]) ==  typeid(Variable))
           ret = _elements[i]->match(term) ;
           if(ret == false)
             return ret;          
      }    
      return ret;      
    }
    else{
      std::cout << "list_other_finish" << std::endl;      
      return value () == term.value();
    }   
  }
public:
  List (): _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}
  // Term * head() const{
  //   return _elements[0];
  // }
  // List * tail() const 
  //   List *ls= new List() ;
  //   return this;
  // }

private:
  vector<Term *> _elements;

};

#endif
