.PHONY: run clean
CC=g++
CFLAGS= -g -Wall -std=c++14

all: prog_col prog_raw

run: prog_col prog_raw
	./prog_col
	./prog_raw

prog_raw.o: prog_raw.cpp
	$(CC) $(CFLAGS) -c prog_raw.cpp

prog_raw: prog_raw.o
	$(CC) $(CFLAGS) prog_raw.o -o prog_raw

prog_col.o: prog_col.cpp
	$(CC) $(CFLAGS) -c prog_col.cpp

prog_col: prog_col.o
	$(CC) $(CFLAGS) prog_col.o -o prog_col

clean:
	rm -rf *.o prog_col prog_raw
