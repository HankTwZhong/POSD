#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <iostream>
#include "atom.h"
using std::string;

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
  Variable(string s):_symbol(s),_value(s){ string tmp_symbol = s; val_ptr = & tmp_symbol;}
  string  symbol() const{
    return _symbol;
  }
  string value()  const{
    return _value;
  }
  // string pass_pointer_to_change_value( Term &term  ) {
  //   if(lftptr){
  //     lftptr->match(term);
  //   }
  //   if(rightptr){
  //     rightptr->match(term);
  //   }
  //   //  lftptr->match(term);
  // }
  bool match( Term &term ){
    bool ret_temp = this->_assignable;
    Variable * ps = dynamic_cast<Variable *> (&term) ;
    if(ps){
      if(ps->_assignable){      
      // lftptr= ps;
      // ps->lftptr = this;
      =ps->val_ptr 
      ret_temp =true;
      }      
      else if(( ((*ps).value()) == value())) {
        ret_temp = true;
      }
      else{
        ret_temp  =false;
      }
    }
    else{
      if( this->_assignable){
        this->_value = term.symbol() ;
        this->_assignable = false;
        if(!lftptr){
        }
        else{
          // pass_pointer_to_change_value(term);          
        }
      }
      else if(this->_value == term.symbol()){
        ret_temp = true;
      }
    }
    
    return ret_temp;
  }

protected:
  bool _assignable = true;
  Variable *lftptr = NULL;
  Variable *rightptr = NULL;
  string *val_ptr= null;

private:
  string _symbol;
  string _value;

  
  // bool _assignable = true;
};


#endif
