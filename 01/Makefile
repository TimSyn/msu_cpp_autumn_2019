.PHONY: run clean test
CC=g++
CFLAGS= -g -Wall -std=c++14

all: calc

calc: calc.o
	$(CC) $(FLAGS) calc.o -o calc

calc.o: calc.cpp
	$(CC) $(FLAGS) -c calc.cpp

run: calc
	./calc "2+-2 *2 + 3/ -1"

test: tests.py calc
	python3 tests.py

clean:
	rm -rf *.o calc
