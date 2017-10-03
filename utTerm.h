#ifndef UTTERM_H
#define UTTERM_H

#include "number.h"
#include "variable.h"
#include "atom.h"

//test Number.value()
TEST (Number,ctor) {
    Number num(0) ;
    num.value();
    ASSERT_EQ("0",num.value());
}
// test Number.symbol()
TEST (Number, symbol) {
    Number num (25);
    num.symbol();
    ASSERT_EQ("25", num.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
    Number num (25);    
    Number num_25 (25);    
    ASSERT_TRUE(num.match(num_25));
}
// ?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
    Number num_25 (25);
    Number num_0(0);
    ASSERT_FALSE(num_25.match(num_0));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
    Number num (25);
    Atom tom("tom");
    ASSERT_FALSE(num.match(tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
    Number num (25);
    Variable X ("X");
     ASSERT_TRUE(num.match(X));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {

    Atom tom("tom");
    Number num(25);
    ASSERT_FALSE(tom.match(num));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {

    Atom tom("tom");
    Variable X("X");
    ASSERT_TRUE(tom.match(X));
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {

    Atom tom("tom");
    Variable X("X");
    ASSERT_TRUE(X.match(tom));
    ASSERT_TRUE( tom.match(X));
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
    Variable X("X");
    Atom jerry ("jerry");
    Atom tom("tom");
    ASSERT_TRUE(X.match(jerry));
    ASSERT_FALSE(tom.match(X));
    
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
    Variable X("X");
    Number num (5);    
    ASSERT_TRUE(X.match(num));
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
    Variable X("X");
    Number num_25 (25);
    Number num_100(100);
    ASSERT_TRUE(X.match(num_25));
    ASSERT_FALSE(X.match(num_100));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {

    Variable X ("X");
    Atom tom("tom");
    Number num_25(25);
    ASSERT_TRUE(X.match (tom));
    ASSERT_FALSE(X.match(num_25));
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
    Atom tom ("tom");
    Variable X("X");
    Number num_25(25);
    ASSERT_TRUE(tom.match(X));
    ASSERT_FALSE(num_25.match(X));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){

    Atom tom("tom");
    Variable X("X");
    ASSERT_TRUE(X.match(tom));
    ASSERT_TRUE(X.match(tom));
}

// // //My test
// // TEST(Number,matchDouble){
// //     Number num (25);
// //     ASSERT_EQ("25",num.value());
// //     Number num2 (25.5);
// //     Number num2
// //     ASSERT_EQ("25.5",num2.value());
// // }
//
#endif
