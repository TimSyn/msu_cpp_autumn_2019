.PHONY: run clean test

CC=g++
CFLAGS=-g -Wall -std=c++14

all: test

run: test
	./test

clean:
	rm -rf *.o test

test: test.cpp format.cpp
	$(CC) $(CFLAGS) test.cpp -o test
