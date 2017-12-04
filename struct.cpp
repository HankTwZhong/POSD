#include "struct.h"
#include "iterator.h"
#include <typeinfo>
#include <iostream>
using namespace std;

Iterator<Term*> * Struct::createIterator(){
  return new StructIterator<Term*>(this);
}
Iterator<Struct*> * Struct::createBFSIterator (){

  // return new BFSIterator(this);
}
//撰寫出一個BFS
vector<Term *> Struct::BFS(){
  queue <Term *> q;
  vector<Term *> tempTer ;
  Struct * converStruct  ;
  Struct * tmpStr ;
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
    tempTer.push_back(q.front());
    q.pop();
  }
  return tempTer;
}

// Iterator * Struct::createDFSIterator(){
  

//   // 寫個DFS的演算法去做抓值
//   // 然後就給他抓下去
// }