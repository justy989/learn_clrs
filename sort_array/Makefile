
CC=g++
CFLAGS=-std=c++1y -Wall -Wextra -Werror -DNDEBUG

debug: CFLAGS:=$(CFLAGS) -g
debug: sort

fast: CFLAGS:=$(CFLAGS) -O3
fast: sort

sort: main.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o sort
