all: hw3
hw3: MainTest.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 MainTest.o -lgtest 
else 
	g++ -o hw3 MainTest.o -lgtest -lpthread
endif

MainTest.o: MainTest.cpp utStruct.h utVariable.h
	g++ -std=c++11 -c MainTest.cpp
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
