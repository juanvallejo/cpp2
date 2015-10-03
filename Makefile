OBJS = utilities.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c
LFLAGS = -Wall $(DEBUG)
PROJECT = project3

.PHONY: all default clean

default: all

all: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(PROJECT) 

utilities.o: utilities.cpp utilities.h
	$(CC) $(CFLAGS) utilities.cpp

main.o: main.cpp utilities.cpp utilities.h
	$(CC) $(CFLAGS) main.cpp

clean:
	if ls *.o 1>/dev/null 2>&1; then rm *.o; fi; if [[ -f $(PROJECT) ]]; then rm $(PROJECT); fi; if [[ -f Results.txt ]]; then rm Results.txt; fi