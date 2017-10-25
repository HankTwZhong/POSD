all: hw4
hw4: mainList.o term.o list.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 mainList.o term.o list.o  -lgtest 
else 
	g++ -o hw4 mainList.o term.o list.o  -lgtest -lpthread
endif

utAtom: mainAtom.o atom.o
	g++ -o utAtom mainAtom.o atom.o -lgtest -lpthread
mainAtom.o: mainAtom.cpp utAtom.h atom.h utStruct.h struct.h
	g++ -std=gnu++0x  -c mainAtom.cpp
atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x  -c atom.cpp
utVariable: mainVariable.o atom.o
		g++ -o utVariable mainVariable.o atom.o -lgtest -lpthread
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ -std=gnu++0x -c mainVariable.cpp
utScanner: mainScanner.o scanner.h utScanner.h
	g++ -o utScanner mainScanner.o -lgtest -lpthread
mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h
		g++ -std=gnu++0x  -c mainScanner.cpp
term.o: term.cpp term.h
	g++ -std=gnu++0x  -c term.cpp
list.o: list.cpp list.h term.h variable.h
	g++ -std=gnu++0x  -c list.cpp
utList: mainList.o term.o list.o
	g++ -o utList mainList.o term.o list.o -lgtest -lpthread
mainList.o: mainList.cpp utList.h
	g++ -std=gnu++0x  -c mainList.cpp

clean:
	rm -f *.o hw4 utList
stat:
	wc *.h *.cpp
