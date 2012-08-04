CC=gcc
CFLAGS=-Wall -pedantic --std=gnu99 -g -ggdb

.PHONY: all clean

all: CameraCal

clean:
	-rm CameraCal CameraCal.o CameraCal2.o

CameraCal: CameraCal.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
