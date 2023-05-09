#include <string.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  CheckArgc(argc, 3);
  storeTxt * cw = readTemp(argv[1]);
  catarray_t * carr = storeCat(cw);
  storeTxt * st = readTemp(argv[2]);
  category_t pre;
  pre.n_words = 0;
  pre.name = strdup("previous words");
  pre.words = NULL;
  processTemp(st, carr, &pre);
  printLine(st);
  freeST(st);
  freeCarr(carr);
  freeST(cw);
  freeCate(&pre);
  return EXIT_SUCCESS;
}
