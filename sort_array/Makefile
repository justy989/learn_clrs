
CC=g++
CFLAGS=-std=c++1y -Wall -Wextra -Werror

fast: CFLAGS:=$(CFLAGS) -O3 -DNDEBUG
fast: sort

debug: CFLAGS:=$(CFLAGS) -g
debug: sort

sort: main.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o sort

