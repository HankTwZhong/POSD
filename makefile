all: hw8
hw8: mainProlog.o struct.o  term.o list.o
ifeq (${OS}, Windows_NT)
	g++ -o hw8 mainProlog.o struct.o  term.o list.o -lgtest 
else 
	g++ -o hw8 mainProlog.o struct.o  term.o list.o -lgtest -lpthread
endif

utAtom: mainAtom.o atom.o
	g++ -o utAtom mainAtom.o atom.o -lgtest -lpthread
mainAtom.o: mainAtom.cpp utAtom.h atom.h utStruct.h struct.h
	g++ -std=gnu++0x  -c mainAtom.cpp
utVariable: mainVariable.o atom.o
		g++ -o utVariable mainVariable.o atom.o -lgtest -lpthread
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ -std=gnu++0x -c mainVariable.cpp
term.o: term.cpp term.h
	g++ -std=gnu++0x  -c term.cpp
list.o: list.cpp list.h 
	g++ -std=gnu++0x  -c list.cpp
struct.o: struct.cpp struct.h 
	g++ -std=gnu++0x  -c struct.cpp
utList: mainList.o term.o list.o
	g++ -o utList mainList.o term.o list.o -lgtest -lpthread
mainList.o: mainList.cpp utList.h
	g++ -std=gnu++0x  -c mainList.cpp
utScanner: mainScanner.o  term.o 
	g++ -o utScanner mainScanner.o term.o -lgtest -lpthread
# mainScanner.o: mainScanner.cpp utScanner.h 
# 		g++ -std=gnu++0x -c mainScanner.cpp
mainScanner.o: mainScanner.cpp TestScanner.h 
	g++ -std=gnu++0x -c mainScanner.cpp
utParser: mainParser.o  term.o list.o struct.o
	g++ -o utParser mainParser.o term.o list.o struct.o -lgtest -lpthread
mainParser.o: mainParser.cpp utParser.h node.h
		g++ -std=gnu++0x -c mainParser.cpp
utIterator: mainIterator.o term.o list.o struct.o 
	g++ -o utIterator mainIterator.o term.o list.o struct.o  -lgtest -lpthread
mainIterator.o: mainIterator.cpp utIterator.h
	g++ -std=gnu++0x -c mainIterator.cpp
# mainProlog.o: mainProlog.cpp utException.h utExpression.h
# 	g++ -std=gnu++0x -c mainProlog.cpp
mainProlog.o: mainProlog.cpp struct.o variable.h term.o number.h list.o iterator.h scanner.h parser.h node.h
	g++ -std=gnu++0x -c mainProlog.cpp


clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw8 utException
endif
stat:
	wc *.h *.cpp
