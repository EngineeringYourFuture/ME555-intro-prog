CPPFLAGS=-Werror -Wall -pedantic -std=gnu++98 -ggdb3
PROGS=test-step1 test-step2 num_sim
all: $(PROGS)

test-step1: test-step1.o myode.o
	g++ -o $@ $^
test-step2: test-step2.o myode.o euler.o
	g++ -o $@ $^
num_sim: num_sim.o myode.o euler.o
	g++ -o $@ $^

%.o: %.cpp
	g++ $(CPPFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ *.o $(PROGS)

myode.o: myode.h
euler.o: euler.h
