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


TEST(iterator, nonNestedStructBFS){
    Number five(5);
    Number seven(7);
    Number nine(9);
    
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z"); 

    Struct s(Atom("s"),{&five,&seven,&nine,&X,&Y,&Z});
    Iterator<Term*>* it = s.createBFSIterator();
    it->first();
    ASSERT_EQ("5", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("7", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("9", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());    
    it->next(); 
    ASSERT_EQ("Z", it->currentItem()->symbol());    
    it->next();    
    it->isDone();
    ASSERT_TRUE(it->isDone());
}
TEST(iterator, StructofBFS_includeList){
    Number one(1);
    Number two(2);
    Number three(3);
    
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");   

    List l({ &Z, &three });    
    Struct t(Atom("t"), { &X, &two, &l });
    Struct s(Atom("s"), { &Y, &t, &two });
    Iterator<Term*>* it = s.createBFSIterator();
    it->first();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->isDone();
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("t(X, 2, [Z, 3])", it->currentItem()->symbol());
    it->isDone();
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());    
    it->next(); 
    ASSERT_EQ("[Z, 3]", it->currentItem()->symbol());    
    it->next();    
    ASSERT_EQ("Z", it->currentItem()->symbol());    
    it->next();    
    ASSERT_EQ("3", it->currentItem()->symbol());    
    it->next();        
    it->isDone();
    ASSERT_TRUE(it->isDone());
    
}
TEST(iterator, StructofDFS_includeList){
    Number one(1);
    Number two(2);
    Number three(3);
    
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");   

    List l({ &Z, &three });    
    Struct t(Atom("t"), { &X, &two, &l });
    Struct s(Atom("s"), { &Y, &t, &two });
    Iterator<Term*>* it = s.createDFSIterator();
    it->first();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->isDone();
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("t(X, 2, [Z, 3])", it->currentItem()->symbol());
    it->isDone();
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[Z, 3]", it->currentItem()->symbol());    
    it->next(); 
    ASSERT_EQ("Z", it->currentItem()->symbol());    
    it->next();       
    ASSERT_EQ("3", it->currentItem()->symbol());    
    it->next();        
    ASSERT_EQ("2", it->currentItem()->symbol());    
    it->next();      
    it->isDone();
    ASSERT_TRUE(it->isDone());
}
TEST(iterator, ListfirstBFSIterator){
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
TEST(iterator, ListfirstDFSIterator){
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

TEST(iterator, ListofDFS_level){
    Number one(1);
    Number two(2);
    Number three(3);
    
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");   

    List l({ &Z, &three });    
    Struct t(Atom("t"), { &X, &two, &l });
    List s({ &Y, &t, &two });
    Iterator<Term*>* it = s.createDFSIterator();
    it->first();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->isDone();
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("t(X, 2, [Z, 3])", it->currentItem()->symbol());
    it->isDone();
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[Z, 3]", it->currentItem()->symbol());    
    it->next(); 
    ASSERT_EQ("Z", it->currentItem()->symbol());    
    it->next();       
    ASSERT_EQ("3", it->currentItem()->symbol());    
    it->next();        
    ASSERT_EQ("2", it->currentItem()->symbol());    
    it->next();      
    it->isDone();
    ASSERT_TRUE(it->isDone());
}

TEST(iterator, ListofBFS_ig){
    Number one(1);
    Number two(2);
    Number three(3);    
    Number four(4);
    Number five(5);
    Number sex(6);    
    Number seven(7);
    Number eight(8);
    Number nine(9);
    List l2l({&eight, &nine});    
    List l2m({&three, &four});
    List l2rin({&sex, &seven});        
    List l2r({&five , &l2rin});
    List l2rr({&one});        
    List l3r({&seven, & sex});    
    List l1rot({ &l2l, &two , &l2m,&l2r ,&l2rr});    

    Iterator<Term*>* it = l1rot.createBFSIterator();
    it->first();
    ASSERT_EQ("[8, 9]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[3, 4]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[5, [6, 7]]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[1]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("8", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("9", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("3", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("4", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("5", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("[6, 7]", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("6", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("7", it->currentItem()->symbol());
    it->next(); 
    it->isDone();
    ASSERT_TRUE(it->isDone());
}
TEST(iterator, ListofDFS_ig){
    Number one(1);
    Number two(2);
    Number three(3);    
    Number four(4);
    Number five(5);
    Number sex(6);    
    Number seven(7);
    Number eight(8);
    Number nine(9);
    List l2l({&eight, &nine});    
    List l2m({&three, &four});
    List l2rin({&sex, &seven});        
    List l2r({&five , &l2rin});
    List l2rr({&one});        
    List l3r({&seven, & sex});    
    List l1rot({ &l2l, &two , &l2m,&l2r ,&l2rr});    
    
    Iterator<Term*>* it = l1rot.createDFSIterator();
    it->first();
    ASSERT_EQ("[8, 9]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("8", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("9", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[3, 4]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("4", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("[5, [6, 7]]", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("5", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("[6, 7]", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("6", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("7", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("[1]", it->currentItem()->symbol());
    it->next(); 
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next(); 
    it->isDone();
    ASSERT_TRUE(it->isDone());
}
#endif
