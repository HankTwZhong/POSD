#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include <iostream>

template <class T>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term* currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template <class T>
class NullIterator :public Iterator <T> {
public:
  NullIterator(Term *n){}
  void first(){}
  void next(){}
  Term * currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }

};
template <class T>
class StructIterator :public Iterator <T> {
public:
  friend class Struct;
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
private:
  StructIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};
template <class T>
class ListIterator :public Iterator <T> {
public:  
  friend class List;  
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
private:
  ListIterator(List *list): _index(0), _list(list) {}
  int _index;
  List* _list;
};
template <class T>
class BFSIterator : public Iterator <T>{
public:
  friend class Struct;
  friend class List;  
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _BFSresult[_index];
  }

  bool isDone() const {
    return (_index >= _BFSresult.size());
  }

  void next() {
    _index++;
  }
private:
  BFSIterator(vector <Term*> BFSresult ): _index(0), _BFSresult(BFSresult) {}
  
  int _index;
  vector<Term*> _BFSresult;
};
template <class T>
class DFSIterator:public Iterator <T> {
public:
  friend class Struct;
  friend class List;  
  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _DFSresult[_index];
  }

  bool isDone() const {
    return (_index >= _DFSresult.size());
  }

  void next() {
    _index++;
  }
private:
  DFSIterator(vector <Term*> DFSresult ): _index(0), _DFSresult(DFSresult) {}  
  int _index;
  vector<Term*> _DFSresult;
};
#endif
