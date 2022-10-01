# Chris Vasquez

CC=g++

FLAG= -g -std=c++11 -pthread

a.out: main.cpp filter.o filter.h
	$(CC) $(FLAG) main.cpp filter.o
filter.o: filter.cpp filter.h
	$(CC) $(FLAG) -c filter.cpp -o filter.o
