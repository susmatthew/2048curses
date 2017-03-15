#this is a makefile
CC = gcc
CFLAGS = -Wall -g -std=c99 -lncurses
DEPS = 2048.h display.h
OBJ = 2048.o display.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

robomake: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)