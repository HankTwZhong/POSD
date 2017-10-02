#ifndef ATOM_H
#define ATOM_H

#include <string>
using std::string;
class Number ;
class Variable ;

class Atom {
public:
  Atom (string s):_symbol(s) {}
  string _symbol;
  bool match(Atom a) ;
  bool match(Number &num);
  bool match(Variable &var);
};

#endif
