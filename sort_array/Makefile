
CC=g++
CFLAGS=-std=c++1y -O3 -Wall -Wextra -Werror -DNDEBUG
EXES=insertion_sort

all: $(EXES)

insertion_sort: insertion_sort.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o $(EXES)
