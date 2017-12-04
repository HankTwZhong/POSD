#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "number.h"
#include "list.h"
#include "iterator.h"
// #include "iteratoroftem.h"
TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    // StructIterator it(&s);
    Iterator<Term*> *itStruct = s.createIterator();
    // Iterator& itStruct = it;
    // ASSERT_EQ(it.first()->symbol());
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator<Term*> *it = s.createIterator();
  it->first();
  it->next();
  Struct *s2 = dynamic_cast<Struct *>(it->currentItem());

  Iterator<Term*> *it2 = s2->createIterator();
  it2->first();
  ASSERT_EQ("X", it2->currentItem()->symbol());
  ASSERT_FALSE(it2->isDone());
  it2->next();
  ASSERT_EQ("2", it2->currentItem()->symbol());
  ASSERT_FALSE(it2->isDone());
  it2->next();
  ASSERT_TRUE(it2->isDone());
}

TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    Iterator<Term*> *itList = l.createIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator){
  Number one(1);
  NullIterator<Term*> nullIterator(&one);
  nullIterator.first();
  ASSERT_TRUE(nullIterator.isDone());
  Iterator<Term*> * it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, StructofBFS_1level){
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &Y, &one, &two });
   
    ASSERT_EQ(4,t.BFS().size());
}
TEST(iterator, StructofBFS_2level){
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t2(Atom("t2"), { &X, &Y});    
    Struct t(Atom("t"), { &one, &t2 , &two });
    
    std::vector<Term *> v = {&X};
    Struct s2(Atom("s2"), v);
    std::vector<Term *> v2 = {&s2};
    Struct s1(Atom("s1"), v2);
    Number pi(3.14);
    X.match(pi);

    ASSERT_EQ(5,t.BFS().size());
    ASSERT_EQ(2,s1.BFS().size());
}

TEST(iterator, firstBFSIterator){
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"),{ &one, &t, &Y });
    Iterator<Term*>* itList = s.createBFSIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    itList->isDone();
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    itList->isDone();
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_EQ("X", itList->currentItem()->symbol());
    itList->next();
    ASSERT_EQ("2", itList->currentItem()->symbol());    
    itList->next();    
    itList->isDone();
    ASSERT_TRUE(itList->isDone());
}
TEST(iterator, firstDFSIterator){
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    List t({ &X, &two });
    List s({&one,&t, &Y});
    Iterator<Term*>* itList = s.createDFSIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    itList->isDone();
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("[X, 2]", itList->currentItem()->symbol());
    itList->isDone();
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("X", itList->currentItem()->symbol());
    itList->next();
    ASSERT_EQ("2", itList->currentItem()->symbol());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());    
    itList->next();    
    itList->isDone();
    ASSERT_TRUE(itList->isDone());
}
  

#endif
