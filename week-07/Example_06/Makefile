CC = gcc
CFLAGS = -fopenmp -Wall -std=c11 -march=native -O2
LDFLAGS = -lm

SOURCES = stencil_opt2.c stencil_opt4.c stencil_opt6.c
EXECUTABLES = $(SOURCES:.c=)
UTILS = timer.o malloc2D.o

all: $(EXECUTABLES)
	@echo "All stencil executables built successfully!"

%: %.c $(UTILS)
	@echo "Building $@..."
	$(CC) $(CFLAGS) $< $(UTILS) -o $@ $(LDFLAGS)

timer.o: timer.c timer.h
	@echo "Compiling timer..."
	$(CC) $(CFLAGS) -c timer.c -o $@

malloc2D.o: malloc2D.c malloc2D.h
	@echo "Compiling malloc2D..."
	$(CC) $(CFLAGS) -c malloc2D.c -o $@

run-opt2: stencil_opt2
	./stencil_opt2

run-opt4: stencil_opt4
	./stencil_opt4

run-opt6: stencil_opt6
	./stencil_opt6

run-all: all
	./stencil_opt2
	./stencil_opt4
	./stencil_opt6

clean:
	rm -f $(EXECUTABLES) $(UTILS)

rebuild: clean all

.PHONY: all clean rebuild run-opt2 run-opt4 run-opt6 run-all
