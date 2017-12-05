#ifndef LIST_H
#define LIST_H

#include "term.h"
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <typeinfo>
#include <iostream>
#include <string>
#include <typeinfo>
#include <iostream>
using std::vector;
using namespace std;

class Struct ;
class Variable ;

class List : public Term {
public:
  string symbol() const ;
  string value() const ;
  bool match(Term & term) ;
public:
  List (): _elements(0) {}
  List (vector<Term *> const & elements):_elements(elements){}
  Term * head() const;
  List * tail() const;
  Term * args(int index) {
    return _elements[index];
  }
  int arity() const {return _elements.size();}  
  Iterator<Term*> * createIterator();
  Iterator<Term*> * createBFSIterator();
  Iterator<Term*> * createDFSIterator();
  vector<Term *> BFS();
  vector<Term *> DFS();  
  void recursiveofDFS(Struct *s , stack<Term*> &stk , vector<Term*> &vec_Ter);  
  void recursiveofDFS(List *l ,  stack<Term*> &stk , vector<Term*> &vec_Ter);
private:
  vector<Term *> _elements;
};

#endif
