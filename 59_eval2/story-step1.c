#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"
//#include "provided.h"

int main(int argc, char ** argv) {
  CheckArgc(argc, 2);
  storeTxt * st = readTemp(argv[1]);
  category_t pre;
  pre.n_words = 0;
  pre.name = strdup("previous words");
  pre.words = NULL;

  processTemp(st, NULL, &pre);
  printLine(st);
  freeST(st);
  freeCate(&pre);
  return EXIT_SUCCESS;
}
