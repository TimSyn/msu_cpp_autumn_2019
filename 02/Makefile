.PHONY: run clean test

CC=g++
CFLAGS = -g -Wall -std=c++14

all: allocator

allocator: allocator.o
	$(CC) $(CFLAGS) allocator.o -o allocator

allocator.o: allocator.cpp
	$(CC) $(CFLAGS) -c allocator.cpp

run: allocator
	./allocator 100 a10 a90 a10 r

test: tests.py allocator
	python3 tests.py

clean:
	rm -rf *.o allocator
