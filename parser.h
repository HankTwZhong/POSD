#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <typeinfo>
using std::string;

#include "term.h"
#include "number.h"
#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"

#include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }
    // if(token == ',' || token == ';' || token == '=' ){
    //   _operation.push_back((char)(token));
    //   std::cout << std::to_string(token) << std::endl;
    // }

    return nullptr;
  }

  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }
  vector<Term *> & getTerms() {
    return _terms;
  }

  void matchings (){

    //1.--藉由某樣樣函式抓取 掃到的東西然後 存到 一個容器
    //  --然後再組裝容器??
    //2.或者 我直接放到node 裡面??
    //  然後就直接建出東西來
    //  而規則就是已知道的那樣
    //  但是這樣順序就會不一致 過於FIFO
    //3.不然就是藉由抓取出來之後再排序
    //  不過誰前誰後就需要撰寫規則
    //4.
    // std::cout << _terms.size() << std::endl;


    createTerms(); //抓取term and operation
    createNode();
    createNodeofRealation();
    for (int i =0 ; i< _terms.size() ; i++ )
    {
      std::cout << _terms[i]->symbol() << std::endl;
    }    
  }
  void createNode (){
    // 先想一個node 具有符號與值的對應
    // 之後存入容器    
    // 建立operation的node
    int EqualityCounter= 0;
    int SymbolofNode;
    vector<Node*> nodeofTerms ;
    for(int i = 0 ; i< _terms.size();i++){
      nodeofTerms.push_back(new Node(TERM,_terms[i],0,0));      
    }    
    for(int i = 0 ; i< _operation.size() ;i++){
      switch (_operation[i]){
        case ';': _nodeofOperation.push_back(new  Node (SEMICOLON));break;
        case ',':_nodeofOperation.push_back(new  Node (COMMA)); break;
        case '=': _nodeofOperation.push_back(new Node (EQUALITY , 0 , nodeofTerms[EqualityCounter],nodeofTerms[EqualityCounter+1])); 
        EqualityCounter +=2;
        break;
        default :break;
      }
    }    
    std::cout << "OperatioN_Size:"+ std::to_string(_operation.size()) <<std::endl;
  }
  void createNodeofRealation(){
    for(int i = 0 ; i< _operation.size() ;i++){
      if(_operation[i] == ','){
        _nodeofOperation[i]->setchild(_nodeofOperation[i-1],_nodeofOperation[i+1]);
        for(int j = i+1 ; j<_operation.size()  ; j++){
          if(_operation[j]==','){
            _nodeofOperation[i]->setchild(_nodeofOperation[i-1],_nodeofOperation[j]);
            break;
          }
        }
      }
    }
    setRoot();
    matchingSameVariable();


  }

  void matchingSameVariable(){    
    vector <Term* > blockofSameVariable ;
    recursive_inorder(_tree,blockofSameVariable);
    for(int i = 0 ; i<blockofSameVariable.size(); i++){
      for(int j=0 ; j<blockofSameVariable.size() ; j++){
        if(blockofSameVariable[i]->symbol() == blockofSameVariable[j]->symbol() && i != j){
          std::cout << "left_ele:"+blockofSameVariable[i]->symbol() + "\t right_ele:" +blockofSameVariable[j]->symbol() <<std::endl;          
          blockofSameVariable[i]->match(*blockofSameVariable[j]);  
          blockofSameVariable.erase(blockofSameVariable.begin()+ j);      
        }        

      }
    }
    std::cout <<"done" <<std::endl;
    
  }

  void recursive_inorder(Node *here , vector<Term*> & v)
  {
    if(here != NULL)
    {
      if(here->left != NULL)
         recursive_inorder(here->left ,v);
      if(here->right != NULL)    
        recursive_inorder(here->right,v);   

      if( here->term != 0 ){
        Variable * varb= dynamic_cast<Variable*>(here->term);
        if(varb){ 
          v.push_back(here->term);                       
        }  
      }
    }
  }
  
  Node * expressionTree(){
    // setRoot();
    return _tree; 
  }
  void setRoot(){
    _tree = _nodeofOperation[0];
    for(int i = 0 ; i < _operation.size() ; i++){
      if(_operation[i] =='='){
        _tree = _nodeofOperation[i];
      }
      if(_operation[i] ==','){
        _tree = _nodeofOperation[i];
        break;        
      }      
    }
  }



private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',' || _currentToken == '=' ||_currentToken == ';') {
        _operation.push_back((_currentToken));
        std::cout << ((char)_currentToken)  << std::endl; // 確認放入的符號
        _terms.push_back(createTerm());
      }
    }
  }

  Node * _tree ;
  vector<Term *> _terms;
  vector<int> _operation;
  vector<Node*> _nodeofOperation;
  Scanner _scanner;
  int _currentToken;
};
#endif
