#include "atom.h"
#include "variable.h"
#include "list.h"

#include <typeinfo>

bool Term::match(Term & a){
  if (typeid(a) ==  typeid(Variable))
    return a.match(*this);
  // else if (typeid (a) == typeid( List)){
  //   return a.match(*this);
  // }
  else
    return symbol() == a.symbol();
}
