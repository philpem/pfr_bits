CC=gcc
CFLAGS=-Wall -pedantic --std=gnu99 -g -ggdb

.PHONY: all clean test

all: CameraCal

clean:
	-rm CameraCal CameraCal.o CameraCal2.o

CameraCal: CameraCal.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

test: CameraCal
	@./CameraCal > tmp && diff tmp reference >/dev/null && echo OK || echo ERROR && rm tmp
