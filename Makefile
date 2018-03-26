CC=gcc
IFLAGS=-I ./include
SRC=src
LFLAGS=-lncurses
OFILE=bin/t


all:
	$(CC) -g -Wall $(SRC)/*.c $(IFLAGS) -o $(OFILE) $(LFLAGS)
