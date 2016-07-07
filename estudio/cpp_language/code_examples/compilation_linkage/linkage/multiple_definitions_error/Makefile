CC=g++
OBJS=a.o b.o
CFLAGS=-c -Wall
LDFLAGS=
HEADERS=header.h
RM=rm -f

MAIN=main
CORE_DUMPS=core.*
TRASH= $(OBJS) $(MAIN).last_diff $(MAIN) $(MAIN).o $(CORE_DUMPS) a.out *.*~ *~ 

clean:
	clear; $(RM) $(TRASH); ls -l


all:a.o


a.o:a.cpp $(HEADERS)
	@echo 'Building target: $@'
	$(CC) $(CFLAGS) $^.cpp
