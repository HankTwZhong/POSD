#ifndef LIST_H
#define LIST_H

#include "term.h"
#include <vector>
#include <string>
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
  string value() const{return symbol();}
public:
  bool match(Term & term) {  }
  List (): _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}
  Term * head() const{
    return _elements[0];
  }
  // List * tail() const 
  //   // List *ls= new List() ;
  // //   // return this;
  // }

private:
  vector<Term *> _elements;

};

#endif
