#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>

#include "provided.h"
void CheckArgc(int argc, int num);
FILE * readFile(const char * filename);
void closeFile(FILE * f);

typedef struct {
  char ** line;
  size_t len;
} storeTxt;

storeTxt * readTemp(const char * filename);
char * repCName(char * line, catarray_t * carr, category_t * pre);
void processTemp(storeTxt * st, catarray_t * car, category_t * pre);
const char * judCName(char * name, catarray_t * carr, category_t * pre);
void printLine(storeTxt * st);
void freeST(storeTxt * st);
catarray_t * storeline(char * line, catarray_t * carr);
catarray_t * storeCat(storeTxt * st);
void freeCate(category_t * cate);
void freeCarr(catarray_t * carr);
#endif
