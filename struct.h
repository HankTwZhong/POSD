#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include <vector>
#include <stack>
#include <string>
#include <queue>
#include <typeinfo>
#include <iostream>
using std::string;
using namespace std;
class List ;
class Struct: public Term {
public:
  Struct(Atom name, std::vector<Term *> args): _name(name) {
    _args = args;
  }

  Term * args(int index) {
    return _args[index];
  }
  int arity(){
    return _args.size();
  }

  Atom & name() {
    return _name;
  }
  string symbol() const {
    if(_args.empty()){
      return _name.symbol() + "()";
    }
    string ret = _name.symbol() + "(";
    std::vector<Term *>::const_iterator it = _args.begin();
    for (; it != _args.end()-1; ++it)
      ret += (*it)->symbol()+", ";
    ret  += (*it)->symbol()+")";
    return ret;
  }
  string value() const {
    string ret = _name.symbol() + "(";
    std::vector<Term *>::const_iterator it = _args.begin();
    for (; it != _args.end()-1; ++it)
      ret += (*it)->value()+", ";
    ret  += (*it)->value()+")";
    return ret;
  }
  Iterator<Term*> * createIterator();
  Iterator<Term*> * createBFSIterator();
  Iterator<Term*> * createDFSIterator();
  std::vector<Term *> BFS();
  std::vector<Term *> DFS();  
  void recursiveofDFS(Struct *s , stack<Term*> &stk , vector<Term*> &vec_Ter);
  void recursiveofDFS(List *l ,  stack<Term*> &stk , vector<Term*> &vec_Ter);
private:
  Atom _name;
  std::vector<Term *> _args;
  
};

#endif
