.PHONY: run clear clean

CC=g++
CFLAGS= -g -Wall -std=c++14

all: test

run: test
	./test

clean:
	rm -rf *.o test

test: big_numbers.h big_numbers.o test.o
	$(CC) $(CFLAGS) big_numbers.o test.o -o test

test.o: test.cpp big_numbers.h
	$(CC) $(CFLAGS) -c test.cpp

big_numbers.o: big_numbers.cpp big_numbers.h
	$(CC) $(CFLAGS) -c big_numbers.cpp
