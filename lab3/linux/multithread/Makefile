# Makefile, ECE254 lab1
# Irene Huang, 2012/09/20

CC=gcc
CFLAGS=-Wall -g
LD=gcc
LDFLAGS=-g -lrt
LM=-lm
PT=-lpthread


OBJS1=sender_master.o

all: produce

produce: $(OBJS1)
	$(LD) $(LDFLAGS) -o $@ $(OBJS1) $(LM) $(PT)
	
sender_master.o: sender_master.c
	$(CC) $(CFLAGS) $(LM) $(PT) -c sender_master.c circular_buffer.h

.PHONY: clean
clean:
	rm -f *.o *.out 
