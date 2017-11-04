all: hw5
hw5: mainParser.o term.o list.o
ifeq (${OS}, Windows_NT)
	g++ -o hw5 mainParser.o term.o list.o  -lgtest 
else 
	g++ -o hw5 mainParser.o term.o list.o  -lgtest -lpthread
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
list.o: list.cpp list.h term.h variable.h
	g++ -std=gnu++0x  -c list.cpp
utList: mainList.o term.o list.o
	g++ -o utList mainList.o term.o list.o -lgtest -lpthread
mainList.o: mainList.cpp utList.h
	g++ -std=gnu++0x  -c mainList.cpp
utScanner: mainScanner.o  term.o 
	g++ -o utScanner mainScanner.o term.o -lgtest -lpthread
mainScanner.o: mainScanner.cpp utScanner.h 
		g++ -std=c++11 -c mainScanner.cpp
utParser: mainParser.o  term.o list.o
	g++ -o utParser mainParser.o term.o list.o -lgtest -lpthread
mainParser.o: mainParser.cpp utParser.h
		g++ -std=c++11 -c mainParser.cpp


clean:
	rm -f *.o  utList utScanner utParser hw5
stat:
	wc *.h *.cpp
