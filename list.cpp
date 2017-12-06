#include "list.h"
#include "struct.h"
#include "variable.h"
#include "iterator.h"


using std::vector;

string List::symbol() const{
    string ret ;
    if(_elements.size()==0 ){
      ret = "[]";
    }
    else{
      ret  = "[";
      std::vector<Term *>::const_iterator it = _elements.begin();
      for( ; it != _elements.end()-1 ; ++it ){
        ret += (*it)->symbol()+", ";
      }
      ret += (*it)->symbol()+"]";
    }
    return ret;
  }
string List::value() const{
    string ret ;
    if(_elements.empty()){
        ret = "[]";
    }
    else{
        ret  = "[";
        std::vector<Term *>::const_iterator it = _elements.begin();
        for( ; it != _elements.end()-1 ; ++it ){
        ret += (*it)->value()+", ";
        }
        ret += (*it)->value()+"]";
}
return ret;
}
bool List::match(Term & term) {
    if(typeid(term) ==  typeid(List)){
        bool ret =true;      
        List * ptrls = dynamic_cast<List*>(&term);
        if( _elements.size() != ptrls->_elements.size() ){
        ret = false;
        }
        else{
            for(int i = 0 ; i < _elements.size() ;i++ ){
                ret = _elements[i]->match(*(ptrls->_elements[i])) ;
                if(ret == false)
                    return ret;    
            }    
        }
        return ret;
    }
    else if(typeid(term) == typeid(Variable)){      
        bool ret =true;                    
        for(int i = 0 ; i < _elements.size() ;i++ ){         
        if(_elements[i]->symbol() ==  term.symbol()){            
            if( _elements[i]->symbol() == term.symbol() ){
                ret= false;
                return ret;
            }
        ret = _elements[i]->match(term) ;    
        }        
        if(ret == false)
                return ret;          
        }    
        return ret;      
    }
    else{    
        return value () == term.value();
    }   
}
Term * List::head() const{
    if(_elements.empty())
        throw std::string("Accessing head in an empty list");

    return _elements[0];    
}
List * List::tail() const {
    if(_elements.empty())
        throw std::string("Accessing tail in an empty list");
    vector<Term *> _clone_elements;
    _clone_elements.assign(_elements.begin()+1, _elements.end());     
    List *ls= new List(_clone_elements) ;
    return ls;
}
Iterator<Term*> * List::createIterator(){
    return new ListIterator<Term*>(this);
}
Iterator<Term*> * List::createBFSIterator (){
    vector <Term*> BFSvec = this->BFS();
    return new BFSIterator<Term*>(BFSvec);
}
Iterator<Term*>* List::createDFSIterator(){
    vector<Term*> DFSvec = this->DFS();
    return new DFSIterator<Term*>(DFSvec);
}
vector<Term*> List::BFS(){
    queue<Term *> que;
    vector<Term *> resultVec;
    Struct * converStruct  ;
    List * converList;
    for(int i = 0 ; i < this->arity() ;i++ ){
        que.push(this->args(i));
        cout << this->args(i)->symbol() << endl;        
    }
    cout << "BFS\tList\tIn:"<< endl;        
    while(!que.empty()){
        converList = dynamic_cast<List*>(que.front());
        converStruct = dynamic_cast<Struct*>(que.front());    
        if(converList){
            for(int i =0 ; i<converList->arity() ; i++){
                que.push(converList->args(i));
                cout << converList->args(i)->symbol() << endl;        
            }
        
        }
        else if(converStruct){
            for(int i = 0 ; i < converStruct->arity() ; i++){
                que.push(converStruct->args(i));
                cout << converStruct->args(i)->symbol() << endl;                        
            }
        }
        resultVec.push_back(que.front());
        cout << (que.front()) << endl;        
        cout << "BFS\tList\tOut:" << endl;
        
        que.pop();
    }
    return resultVec;
}

vector<Term *> List::DFS(){
    stack <Term *> stk;
    vector<Term *> resultVec ;
    Struct * converStruct  ;    
    List * converList  ;
    for(int i = 0  ;  i < this->arity() ; i ++){
      stk.push(this->args(i));      
      converList = dynamic_cast<List*>(stk.top());
      converStruct = dynamic_cast<Struct*>(stk.top());      
      resultVec.push_back(stk.top());
      if(converList){
        recursiveofDFS(converList,stk,resultVec);    
      }
      else if(converStruct){
        recursiveofDFS(converStruct,stk,resultVec);   
      }
      stk.pop();
    }
    return resultVec;
}

void List::recursiveofDFS (List *l , stack<Term*> &stk , vector<Term*> &resultVec){
    List * converList  ;  
    Struct * converStruct  ;  
    for(int i = 0  ;  i < l->arity() ; i ++){
      stk.push(l->args(i));      
      resultVec.push_back(stk.top());
      converList = dynamic_cast<List*>(stk.top());
      converStruct = dynamic_cast<Struct*>(stk.top());
      if(converList) {
        recursiveofDFS(converList,stk,resultVec);    
      }
      else if(converStruct){
        recursiveofDFS(converStruct,stk,resultVec);          
      }
      stk.pop();
    }
}
void List::recursiveofDFS(Struct *s,stack<Term*> &stk , vector<Term*> &resultVec){
    Struct * converStruct  ;    
    List * converList;  
    for(int i = 0  ;  i < s->arity() ; i ++){
      stk.push(s->args(i));      
      resultVec.push_back(stk.top());
      converList = dynamic_cast<List*> (stk.top()); 
      converStruct = dynamic_cast<Struct*>(stk.top());      
      if(converStruct) {
        recursiveofDFS(converStruct,stk,resultVec);    
      }
      else if(converList){
        recursiveofDFS(converList,stk,resultVec);          
      }
      stk.pop();
    }
 }

