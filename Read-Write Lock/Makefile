# Chris Vasquez

CC=g++
FLAG= -g -std=c++11 -pthread

a.out: main.cpp ReadWriteLock.o ReadWriteLock.h
	$(CC) $(FLAG) main.cpp ReadWriteLock.o
ReadWriteLock.o: ReadWriteLock.cpp ReadWriteLock.h
	$(CC) $(FLAG) -c ReadWriteLock.cpp -o ReadWriteLock.o
