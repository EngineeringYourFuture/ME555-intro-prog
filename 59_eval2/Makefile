CFLAGS=-std=gnu99 -pedantic -Wall -Werror -ggdb3
PROGS=story-step1 story-step2 story-step3 story-step4
OBJS=$(patsubst %.c,%.o, story-step*.c rand_story.c)

all: $(PROGS)

story-step%: story-step%.o rand_story.o provided.o
	gcc -o $@ $^

%.o: %.c
	gcc $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f $(OBJS) *~ $(PROGS)

rand_story.o: rand_story.h
