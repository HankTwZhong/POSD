#include "struct.h"
#include "iterator.h"

using namespace std;

Iterator<Term*> * Struct::createIterator(){
  return new StructIterator<Term*>(this);
}

Iterator<Term*> * Struct::createBFSIterator (){
  vector <Term*> BFSvec = this->BFS();
  return new BFSIterator<Term*>(BFSvec);
}

Iterator<Term*> * Struct::createDFSIterator (){
  vector <Term*> DFSvec = this->DFS();
  return new DFSIterator<Term*>(DFSvec);
}

vector<Term *> Struct::BFS(){
  queue <Term *> q;
  vector<Term *> resultVec ;
  Struct * converStruct  ;
  for(int i = 0  ;  i < this->arity() ; i ++){
    q.push(this->args(i));
  }
  while(!q.empty()){
    converStruct = dynamic_cast<Struct*>(q.front());
    if(converStruct){
      for(int i = 0  ;  i < converStruct->arity() ; i ++){
        q.push(converStruct->args(i));
      }
    }
    //elseif ------List
    resultVec.push_back(q.front());
    q.pop();
  }
  return resultVec;
}

vector<Term *> Struct::DFS(){
  stack <Term *> stk;
  vector<Term *> resultVec ;
  Struct * converStruct  ;
  for(int i = 0  ;  i < this->arity() ; i ++){
    stk.push(this->args(i));      
    converStruct = dynamic_cast<Struct*>(stk.top());
    resultVec.push_back(stk.top());
    if(converStruct){
      recursiveofDFS(converStruct,stk,resultVec);    
    }
    //else if list
    stk.pop();
  }
  return resultVec;
}

void Struct::recursiveofDFS (Struct *s,stack<Term*> &stk , vector<Term*> &resultVec){
  Struct * converStruct  ;  
  for(int i = 0  ;  i < s->arity() ; i ++){
    stk.push(s->args(i));      
    resultVec.push_back(stk.top());
    converStruct = dynamic_cast<Struct*>(stk.top());
    if(converStruct) {
      recursiveofDFS(converStruct,stk,resultVec);    
    }
    //else if list
    stk.pop();
  }
}