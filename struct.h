#ifndef STRUCT_H
#define STRUCT_H

#include <vector>
#include <string>
#include "atom.h"
#include "variable.h"

using std::string;
class Struct:public Term
{
public:
    Struct(Atom const &name , std::vector<Term*> args):_name(name),_args(args){}
    
    Term * args (int index){
        return _args[index];
    }
    Atom const & name (){
        return _name;
    }
    string symbol() const {
        string ret = _name.symbol() + "(" ;
        for(int i = 0; i < _args.size() - 1 ; i++){
            ret += _args[i]-> symbol() + ", ";
        }
        ret += _args[_args.size()-1]-> symbol() + ")";
        return  ret;        
    }
    string value() const {
        string ret =_name.symbol() + "(";
        int tp =0;
        // std::cout  <<"name:"+ _name.symbol() <<endl;
        // std::cout  << "size:"+ to_string( _args.size())  <<endl;
        
        for(int i = 0; i < _args.size() - 1 ; i++){      
            // Variable * typIsVariable = dynamic_cast<Variable *> (_args[i]);
            // if(typIsVariable){
            //     ret += typIsVariable-> value() + ", "; 
            // }
            // else{
            //     ret += _args[i]-> value() + ", "; 
            // }

            // tp=i;
            // std::cout  << "index:"+to_string(tp) <<endl;
            // std::cout  << "value:"+_args[i]-> value() +", " <<endl;            
            ret += _args[i]-> value() + ", "; 
        }   
        // Variable vm ;
        // Variable * typIsVariable2 = dynamic_cast<Variable *> (_args[_args.size()-1]);
        // if(typIsVariable2){
        //     ret += typIsVariable2-> value() + ")"; 
        // }
        // else{
        //     ret += _args[_args.size()-1]-> value() + ")"; 
        // }
        // std::cout  << "final:"+ to_string(_args.size()-1) <<endl;
        // std::cout  << _name.symbol()+" value:"+ _args[_args.size()-1]-> value()  <<endl;            
        
        ret += _args[_args.size()-1]-> value() + ")"; 
        return  ret;
    }
    bool match (Term &term){
        Struct * ps = dynamic_cast<Struct *> (&term);
        if(ps){
            if(!_name.match(ps->_name))
                return false;
            if(_args.size() !=ps->_args.size()){
                return false;
            }
            for(int i =0;i<_args.size();i++ ){
                if(_args[i]->symbol() != ps->_args[i]->symbol())
                return false;
            }
            return true;
        }
        return false;
    }
private:
    Atom _name ;
    std::vector<Term *> _args;
};
#endif