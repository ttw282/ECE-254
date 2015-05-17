
# Makefile, OS lab0
# Irene Huang, 2012/09/16

CC=gcc
CFLAGS=-Wall -g
LD=gcc
LDFLAGS=-g

OBJS2=ls_fname.o

all: ls_fname.out

ls_fname.out: $(OBJS2) 
	$(LD) $(LDFLAGS) -o $@ $^ 

.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o *.out 
