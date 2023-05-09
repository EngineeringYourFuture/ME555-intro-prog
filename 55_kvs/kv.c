#include "kv.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void splitPair(kvpair_t * kvpairs, char * line) {
  char * equal = strchr(line, '=');
  assert(equal != NULL);
  *equal = '\0';
  kvpairs->key = line;
  char * end = strchr(equal + 1, '\n');
  if (end != NULL) {
    *end = '\0';
    kvpairs->value = equal + 1;
  }
  else {
    kvpairs->value = NULL;
  }
  /*size_t key_len = equal - line;
  kvpairs->key = strndup(line, key_len);
  char * end = strchr(equal + 1, '\n');
  if (end != NULL) {
    size_t value_len = end - equal - 1;
    kvpairs->value = strndup(equal + 1, value_len);
  }
  else {
    kvpairs->value = strdup(equal + 1);
  }*/
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  kvarray_t * kvarray = malloc(sizeof(*kvarray));
  assert(kvarray != NULL);
  kvarray->kvpairs = malloc(sizeof(*kvarray->kvpairs));
  assert(kvarray->kvpairs != NULL);
  kvarray->len = 0;
  char * line = NULL;
  size_t sz = 0;
  FILE * f = fopen(fname, "r");
  assert(f != NULL);
  while (getline(&line, &sz, f) >= 0) {
    kvarray->len++;
    kvarray->kvpairs =
        realloc(kvarray->kvpairs, kvarray->len * sizeof(*kvarray->kvpairs));
    splitPair(&kvarray->kvpairs[kvarray->len - 1], line);
    line = NULL;
  }
  free(line);
  assert(!fclose(f));
  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i++) {
    free(pairs->kvpairs[i].key);
    //  free(pairs->kvpairs[i].value);
  }
  free(pairs->kvpairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvpairs[i].key, pairs->kvpairs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->len; i++) {
    if (!strcmp(pairs->kvpairs[i].key, key)) {
      return pairs->kvpairs[i].value;
    }
  }
  return NULL;
}
