all: utAtom utVariable utScanner
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

#utTerm: mainTerm.o term.o struct.o var.o list.o
#	g++ -o utTerm mainTerm.o term.o var.o struct.o list.o -lgtest -lpthread
#mainTerm.o: mainTerm.cpp utTerm.h term.h var.h utStruct.h struct.h list.h utList.h
#	g++ -std=gnu++0x  -c mainTerm.cpp
term.o: term.cpp term.h
	g++ -std=gnu++0x  -c term.cpp
#struct.o: struct.h struct.cpp
#	g++ -std=gnu++0x  -c struct.cpp
#var.o: var.h var.cpp
#g++ -std=gnu++0x  -c var.cpp
utList: mainList.o term.o
	g++ -o utList mainList.o term.o -lgtest -lpthread
mainList.o: mainList.cpp utList.h 
	g++ -std=gnu++0x  -c mainList.cpp
clean:
	rm -f *.o madRace utAtom utVariable utScanner
stat:
	wc *.h *.cpp
