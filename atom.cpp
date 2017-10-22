#include "atom.h"
#include "variable.h"
#include <string>
using std::string;

bool Term::match(Term & term) { 
    Variable * matchTermIsVariable = dynamic_cast<Variable * > (&term);
    if(matchTermIsVariable){
        return matchTermIsVariable->match(*this);
    }
    else{
        return symbol() == term.symbol();
    }
}
