CFLAGS=-std=gnu99 -Wall -Werror -pedantic

all: step1 step2 step3

step1: step1.c
	gcc -o step1 $(CFLAGS) step1.c

step2: step2.c
	gcc -o step2 $(CFLAGS) step2.c

step3: step3.c
	gcc -o step3 $(CFLAGS) step3.c

.PHONY: clean
clean:
	rm -f *~ step1 step2 step3
