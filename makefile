all: hw2
hw2: MainTerm.o Number.o Variable.o Atom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 MainTerm.o Number.o Variable.o Atom.o -lgtest 
else 
	g++ -o hw2 MainTerm.o Number.o Variable.o Atom.o -lgtest -lpthread
endif

MainTerm.o:  MainTerm.cpp utTerm.h number.h variable.h atom.h 
	g++ -std=gnu++0x -c MainTerm.cpp 
Number.o:  Number.cpp  number.h variable.h atom.h 
	g++ -std=gnu++0x -c Number.cpp
Variable.o:  Variable.cpp  variable.h  number.h  atom.h
	g++ -std=gnu++0x -c Variable.cpp
Atom.o:  Atom.cpp  atom.h number.h variable.h
	g++ -std=gnu++0x -c Atom.cpp variable.h

clean:
	rm -f *.o hw2 
stat:
	wc *.h *.cpp 
