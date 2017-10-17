#include "atom.h"
#include "number.h"
#include "variable.h"

#include <string>
using std::string;

bool Atom::match(Atom a) {return _symbol == a._symbol;}
bool Atom::match(Number &num){return false;}
bool Atom::match(Variable &var){
    Atom thisAtom =*this;
    return var.match(thisAtom);
}
