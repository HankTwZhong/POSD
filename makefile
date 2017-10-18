all: hw3
hw3: MainTest.o 
ifeq (${OS}, Windows_NT)
	g++ -o hw3 MainTest.o -lgtest 
else 
	g++ -o hw3 MainTest.o -lgtest -lpthread
endif

MainTest.o: MainTest.cpp utStruct.h utVariable.h
	g++ -std=c++11 -c MainTest.cpp
clean:
	rm -f *.o  hw3
stat:
	wc *.h *.cpp 
