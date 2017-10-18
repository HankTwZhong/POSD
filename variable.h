#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include <iostream>
#include "atom.h"
// #include "struct.h"

using std::string;
using namespace std;

// class CallBackClass
// {
//   // 宣告回呼函式的原型;
//   typedef void (*CBFun)( int k );
//   // 宣告一個回呼函式指標;
//   CBFun pCBFun;
//   public:
//   CallBackClass() { pCBFun= NULL; }// 初始化;
//   void SetCallBack( CBFun fun ) { pCBFun= fun; }//註冊callback函式

//   void run() { 
//   //do something
//   (*pCBFun)( i );//呼叫到callback function
//   };

//   void myCBFun( int k )
//   {
    
//   }
//   int main( int argc, char* argv[] )
//   {
//   CallBackClass cbc;
//   cbc.SetCallBack( myCBFun );//註冊callback函式
//   cbc.run();
//   return 0;
//   }
// };

class Variable : public Term{
public:
  Variable(string s):_symbol(s),_value(s){ string* val = &_value; val_ptr = val;  (*community).push_back(this); }
  string  symbol() const{
    return _symbol;
  }
  string value()  {
    return (*val_ptr) ;
  }

  bool match( Term &term ){
    bool ret_temp = this->_did_not_assign_the_class_before;
    Variable * match_Variable = dynamic_cast<Variable *> (&term) ;
    // Struct * Match_Struct =dynamic_cast<Struct *> (&term);
    if(match_Variable){
      if(match_Variable->_did_not_assign_the_class_before){   
        //一個共有的區間 放置 vector指標來進行存放
        community->push_back( match_Variable  );           
        match_Variable ->community = ( community) ;        
        // (* val_ptr) = (* val_ptr) + *(match_Variable->val_ptr);
        // val_ptr = match_Variable->val_ptr;          
      ret_temp =true;
      }      
      else if(( ((*match_Variable).value()) == value())) {
        ret_temp = true;
      }
      else{
        if(this->_did_not_assign_the_class_before){
          // *val_ptr = *val_ptr + *(match_Variable->val_ptr); 
          //  val_ptr = match_Variable->val_ptr;  
          val_ptr = match_Variable->val_ptr;
          this->_did_not_assign_the_class_before = false;
          ret_temp  = true;           
        }
        else
          ret_temp  =false;
      }
    }    
    else{
      if(this->_did_not_assign_the_class_before){
        *val_ptr = term.symbol() ;
        std::cout <<symbol()+" match "+*val_ptr  << std::endl;
        std::cout <<symbol()+" :PTR "+*val_ptr << std::endl;
        std::cout << symbol()+" value:"+ value() << std::endl;
        
        
        for(int i = 0; i < community->size()  ; i++){
          if( ((*community)[i])->val_ptr != val_ptr ){
            cout << "community index : "+ to_string(i)+" symbol :"+ (*community)[i]->symbol()+" ; Value: " + (*community)[i]->value() <<endl;
            (*community)[i]->val_ptr = val_ptr;
            cout << (*community)[i]->symbol() +"  be ASSIGN_PTR : " + *((*community)[i]->val_ptr)  <<endl;
            
          }
        }  
        this->_did_not_assign_the_class_before = false;

      }
      else if(*val_ptr == term.symbol()){        
        ret_temp = true;
      }
      
    }
    
    return ret_temp;
  }

protected:
  bool _did_not_assign_the_class_before = true;
  Variable *lftptr = NULL;
  Variable *rightptr = NULL;
  string *val_ptr= NULL;
  std::vector <Variable *> *community = new std::vector<Variable*>();
  

private:
  string _symbol;
  string _value;

};


#endif
