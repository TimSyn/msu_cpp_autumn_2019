.PHONY: run test clean

CC=g++
CFLAGS= -g -Wall -std=c++14

all: test

clean:
	rm -rf *.o test

run: test
	./test

test: test.o
	$(CC) $(CFLAGS) test.o -o test

test.o: test.cpp matrix.h
	$(CC) $(CFLAGS) -c test.cpp
