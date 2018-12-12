#!/bin/makefile

SRC=$(wildcard *.c)
OFILES=$(SRC:.o=.c)
EXEC=mmake
EXECPP=mmake++

LDFLAGS=
CFLAGS=-Wall -Wextra -ansi -pedantic -Wextra -Wchar-subscripts -Wdouble-promotion -Werror -Wcomment -Wformat

CC=gcc

CLEAN=*.o *~

all:$(EXEC)

cpp:$(EXECPP)

$(EXECPP):$(OFILES)
	$(CC) $^ -o $@ $(LDFLAGS) -D CPP

$(EXEC):$(OFILES)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o:%.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm $(CLEAN)
clear: clean

cleaner:
	rm $(EXEC) $(CLEAN)
