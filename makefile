all: hw2
hw2: mainTerm.o number.o variable.o atom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 mainTerm.o number.o variable.o atom.o -lgtest 
else 
	g++ -o hw2 mainTerm.o number.o variable.o atom.o -lgtest -lpthread
endif

#utTerm: mainTerm.o number.o variable.o atom.o
	#g++ -o utTerm mainTerm.o number.o variable.o atom.o -lgtest -lpthread
mainTerm.o:  mainTerm.cpp utTerm.h number.h variable.h atom.h 
	g++ -std=gnu++0x -c mainTerm.cpp 
number.o:  number.cpp  number.h variable.h atom.h 
	g++ -std=gnu++0x -c number.cpp
variable.o:  variable.cpp  variable.h  number.h  atom.h
	g++ -std=gnu++0x -c variable.cpp
atom.o:  atom.cpp  atom.h number.h variable.h
	g++ -std=gnu++0x -c atom.cpp variable.h


#exp: mainExp.o
#	g++ -o exp mainExp.o -lgtest -lpthread
#mainExp.o: mainExp.cpp exp.h global.h
#	g++ -std=c++11 -c mainExp.cpp

#utScannerParser: mainScannerParser.o term.o struct.o var.o list.o
#	g++ -o utScannerParser mainScannerParser.o term.o var.o struct.o list.o -lgtest -lpthread
#mainScannerParser.o: mainScannerParser.cpp utScanner.h utParser.h scanner.h parser.h term.h var.h struct.h list.h global.h node.h
#		g++ -std=c++11 -c mainScannerParser.cpp

#utTerm: mainTerm.o term.o struct.o var.o list.o
#	g++ -o utTerm mainTerm.o term.o var.o struct.o list.o -lgtest -lpthread
#mainTerm.o: mainTerm.cpp utTerm.h term.h var.h utStruct.h struct.h list.h utList.h
#	g++ -std=c++11 -c mainTerm.cpp
#term.o: term.h term.cpp
#	g++ -std=c++11 -c term.cpp
#struct.o: struct.h struct.cpp
#	g++ -std=c++11 -c struct.cpp
#var.o: var.h var.cpp
#g++ -std=c++11 -c var.cpp
#list.o: list.h list.cpp term.h var.h
#	g++ -std=c++11 -c list.cpp
clean:
	rm -f *.o hw2 utTerm
stat:
	wc *.h *.cpp 
