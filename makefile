dir_INC = include

all: hw1
hw1: main.o Media.o Shapes.o Sort.o
ifeq (${OS}, Windows_NT)
	g++ -o hw1 main.o Media.o Shapes.o  Sort.o -lgtest 
else 
	g++ -o hw1 main.o Media.o Shapes.o Sort.o -lgtest -pthread
endif
main.o: main.cpp utSort.h
	g++ -std=gnu++0x -c main.cpp
Media.o: Media.cpp $(dir_INC)/Media.h
	g++ -std=gnu++0x -c Media.cpp
Shapes.o: Shapes.cpp $(dir_INC)/Shapes.h
	g++ -std=gnu++0x -c Shapes.cpp
Sort.o: Sort.cpp $(dir_INC)/Sort.h
	g++ -std=gnu++0x -c Sort.cpp
clean:  
ifeq (${OS}, Window_NT)
	del *.o *.exe
else
	rm -f *.o hw1
endif