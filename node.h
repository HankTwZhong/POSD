#ifndef NODE_H
#define NODE_H
#include "term.h"

enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

class Node {
public:
  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}

  void setchild(Node *l, Node *r){
    left = l ;
    right = r;
  }

  bool evaluate(){
    
    if(payload == COMMA  ){
      return (left->evaluate() && right->evaluate()) ;
    }
    else if(payload == SEMICOLON){
      return (left->evaluate() || right->evaluate()) ;      
    }
    else if(payload == EQUALITY){
      std::cout << "evaluate leftSide:"+left->term->symbol()+"\t rightSide:"+right->term->symbol() << std::endl;
      return (left->term->match(*(right->term))) ;      
    }
    return false;
  }
  Operators payload ;    

public:
  Term* term ;
  Node* left ;
  Node* right ;
};

#endif
