#include "outname.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  assert(inputName != NULL);
  const char * str = ".counts";
  char * ptr = malloc((strlen(inputName) + strlen(str) + 2) * sizeof(*inputName));
  strcpy(ptr, inputName);
  strcat(ptr, str);
  return ptr;
}
