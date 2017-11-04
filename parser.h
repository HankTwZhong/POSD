#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include <iostream>
#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "number.h"

using namespace std;


class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}
  Term* createTerm(){
    int token = _scanner.nextToken();
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM){
        Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
        vector <Term*> Struct_Param ={};
        if(_scanner.currentChar() == '(') {
          _scanner.nextToken();
          if(_scanner.currentChar() !=  ')' )
            Struct_Param = getArgs() ;
        return new Struct (*atom , Struct_Param);
        }
        else
          return atom;
    }
    else if (token == '[') {
      
      vector<Term*> List_Parm;

      if(_scanner.currentChar() == ']'){

        while(_scanner.buffersize() > _scanner.position() && _scanner.currentChar() != ')'){             
          // NextParse = createTerm();
  
        } 
      }
      else               
        return new List ;
    }
    return nullptr;
  }

  vector<Term*> getArgs()
  {    
      Term* term = createTerm();
      vector<Term*> args;
      if(term)
        args.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        args.push_back(createTerm());
      }
      return args;
  }




private:
  Scanner _scanner;
  int _currentToken;
};
#endif
