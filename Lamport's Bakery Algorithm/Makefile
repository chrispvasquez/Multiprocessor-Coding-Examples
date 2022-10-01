# Chris Vasquez

CC=g++

FLAG= -g -std=c++11 -pthread

a.out: main.cpp bakery.o bakery.h
	$(CC) $(FLAG) main.cpp bakery.o
bakery.o: bakery.cpp bakery.h
	$(CC) $(FLAG) -c bakery.cpp -o bakery.o
