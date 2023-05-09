CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
intMatrixTest: IntMatrix.o test.o
	g++ -o intMatrixTest $(CCFLAGS) IntMatrix.o test.o

%.o: %.cpp IntMatrix.h
	g++ -c $(CCFLAGS) $<

clean:
	rm -f *.o  *~ intMatrixTest
