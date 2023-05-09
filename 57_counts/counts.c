#include "counts.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * array = malloc(sizeof(*array));
  array->c_array = NULL;
  array->len = 0;
  array->c_unknown = 0;
  return array;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  assert(c != NULL);
  //When name is NULL
  if (name == NULL) {
    c->c_unknown++;
    return;
  }
  //When name exist in array
  for (size_t i = 0; i < c->len; i++)
    if (strcmp(c->c_array[i].name, name) == 0) {
      c->c_array[i].count++;
      return;
    }
  //When name does not exist in array
  c->len++;
  c->c_array = realloc(c->c_array, c->len * sizeof(*c->c_array));
  one_count_t new_name;
  new_name.count = 1;
  new_name.name = strdup(name);
  c->c_array[c->len - 1] = new_name;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  assert(c != NULL);
  for (size_t i = 0; i < c->len; i++) {
    fprintf(outFile, "%s: %d\n", c->c_array[i].name, c->c_array[i].count);
  }
  if (c->c_unknown != 0) {
    fprintf(outFile, "<unknown> : %zu\n", c->c_unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->len; i++) {
    free(c->c_array[i].name);
  }
  free(c->c_array);
  free(c);
}
