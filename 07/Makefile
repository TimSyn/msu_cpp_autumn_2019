.PHONY: all run clean

CC=g++
CFLAGS= -std=c++14 -g -Wall

all: test

run: test
	./test

test: test.cpp my_vector.h
	$(CC) $(CFLAGS) test.cpp -o test

clean:
	rm -rf *.o test
