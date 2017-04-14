CFLAGS= -W -Wall -g

all: tldmonitor

clean:
		rm -f *.o tldmonitor

tldmonitor: tldmonitor.o date.o tldlist.o
		cc -o tldmonitor tldmonitor.o date.o tldlist.o

tldmonitor.o: tldmonitor.c date.h tldlist.h

date.o: date.c date.h

tldlist.o: tldlist.c tldlist.h
