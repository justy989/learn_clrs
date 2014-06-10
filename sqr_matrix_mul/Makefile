
include ../utils/Makefile

all: sqr_mat_mul

sqr_mat_mul: matrix.o main.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f sqr_mat_mul

%.o : %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
