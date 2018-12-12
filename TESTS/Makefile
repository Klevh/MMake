#!/bin/makefile

SRC=$(wildcard *.cpp)
OFILES=$(SRC:.o=.cpp)
EXEC=a.out
LDFLAGS=
CFLAGS=
CC=g++
CLEAN=*.o *~

all:$(EXEC)

$(EXEC):$(OFILES)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o:%.cpp
	$(CC) -c $< $(CFLAGS)

clean:
	rm $(CLEAN)

clear: clean

cleaner:
	rm $(EXEC) $(CLEAN)

