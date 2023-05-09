CFLAGS=-std=gnu99 -ggdb3 -pedantic -Wall -Werror

all: printRoster printStats printDoubleDouble printPosPoints
print%: print%.o stats.o
	gcc -o $@ $< stats.o
stats.o: stats.c
	gcc -c $(CFLAGS) $<

.PHONY: clean
clean:
	rm -f *~ printRoster printStats printDoubleDouble printPosPoints stats.o
