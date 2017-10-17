all: hw2
hw2: MainTerm.o Number.o Variable.o Atom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 MainTerm.o Number.o Variable.o Atom.o -lgtest 
else 
	g++ -o hw2 MainTerm.o Number.o Variable.o Atom.o -lgtest -lpthread
endif

MainTerm.o:  MainTerm.cpp utTerm.h number.h variable.h atom.h 
	g++ -std=c++11  -c MainTerm.cpp 
Number.o:  Number.cpp  number.h variable.h atom.h 
	g++ -std=c++11 -c Number.cpp
Variable.o:  Variable.cpp  variable.h  number.h  atom.h
	g++ -std=c++11  -c Variable.cpp
Atom.o:  Atom.cpp  atom.h number.h variable.h
	g++ -std=c++11 -c Atom.cpp variable.h
utStruct: MainStruct.o
	g++ -o utStruct  MainStruct.o -lgtest -lpthread
MainStruct.o: MainStruct.cpp utStruct.h
	g++ -std=c++11 -c MainStruct.cpp
utVariable: MainVariable.o
	g++ -o utVariable  MainVariable.o -lgtest -lpthread
MainVariable.o: MainVariable.cpp utVariable.h
	g++ -std=c++11 -c MainVariable.cpp

clean:
	rm -f *.o utStruct utVariable
stat:
	wc *.h *.cpp 
