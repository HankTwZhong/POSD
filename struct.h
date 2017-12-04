#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include <vector>
#include <string>
#include <queue>

using std::string;

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
  Iterator<Struct*> * createBFSIterator();
  Iterator<Struct*> * createDFSIterator();
  std::vector<Term *> BFS();
private:
  Atom _name;
  std::vector<Term *> _args;
  
};

#endif
