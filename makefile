all: hw3
hw3: MainTest.o atom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 MainTest.o atom.o -lgtest 
else 
	g++ -o hw3 MainTest.o atom.o -lgtest -lpthread
endif

MainTest.o: MainTest.cpp utStruct.h utVariable.h
	g++ -std=gnu++0x -c MainTest.cpp
atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp 

clean:
	rm -f *.o *.exe  hw3
stat:
	wc *.h *.cpp 
