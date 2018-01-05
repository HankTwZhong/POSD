// #include <gtest/gtest.h>
// #include "utException.h"
// #include "utExpression.h"
// int main(int argc, char **argv)
// {
// 	testing::InitGoogleTest(&argc, argv);
// 	return RUN_ALL_TESTS();
// }
#include "term.h"
#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "number.h"
#include "list.h"
#include "iterator.h"
#include "scanner.h"
#include "parser.h"
#include <iostream>
#include <gtest/gtest.h>
#include "utException.h"
#include "utExpression.h"
using namespace std;


int testFile (int argc, char **argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

int main(int argc, char **argv) {
	testFile(argc,argv);
	string sentence ;
	while (cin >> sentence){
		try {
		Scanner s (sentence);
		Parser p(s);
		p.buildExpression();
		string result = p.runEveluate();
		cout << result << endl;
		}catch (string &s){
			cout << s << endl;			
		}
	}
}

