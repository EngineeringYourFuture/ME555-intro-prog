#include "rand_story.h"
int main(int argc, char ** argv) {
  CheckArgc(argc, 2);
  storeTxt * cw = readTemp(argv[1]);
  catarray_t * carr = storeCat(cw);
  printWords(carr);
  freeCarr(carr);
  freeST(cw);
  return EXIT_SUCCESS;
}
