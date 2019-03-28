all: prog clean

prog:prog.cpp matrix.o main.o
	g++ -std=c++11 prog.cpp -o project1 -g -Wall
main.o:main.cpp
	g++ -std=c++11 -Wall -g -c main.cpp

matrix.o:matrix.cpp
	g++ -std=c++11 -Wall -g -c matrix.cpp

clean:
	rm -rf *o
	
