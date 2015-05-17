# Makefile, ECE254 lab1
# Irene Huang, 2012/09/20

CC=gcc
CFLAGS=-Wall -g
LD=gcc
LDFLAGS=-g -lrt
LM=-lm


OBJS1=sender_master.o
OBJS2=sender.o
OBJS3=receiver.o

all: sender.out receiver.out produce

produce: $(OBJS1)
	$(LD) $(LDFLAGS) -o $@ $(OBJS1)
	
sender_master.o: sender_master.c
	$(CC) $(CFLAGS) -c sender_master.c

sender.out: $(OBJS2) 
	$(LD) $(LDFLAGS) -o $@ $(OBJS2) 

sender.o: sender.c
	$(CC) $(CFLAGS) -c sender.c 

receiver.out: $(OBJS3) 
	$(LD) $(LDFLAGS) $(LM) -o $@ $(OBJS3) 

receiver.o: receiver.c
	$(CC) $(CFLAGS) -c receiver.c


.PHONY: clean
clean:
	rm -f *.o *.out 
