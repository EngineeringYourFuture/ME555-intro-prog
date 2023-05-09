#include "rand_story.h"

#include <stdio.h>
#include <string.h>
//check the # arguments
void CheckArgc(int argc, int num) {
  if (argc != num) {
    fprintf(stderr, "Wrong # command line argument.\n");
    exit(EXIT_FAILURE);
  }
  return;
}

//Open file and check the error
FILE * readFile(const char * filename) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }
  return f;
}

//Close file and check error
void closeFile(FILE * f) {
  if (fclose(f) != 0) {
    fprintf(stderr, "Fail to close file.\n");
    exit(EXIT_FAILURE);
  }
  return;
}

//store the input file into a struct storeTxt
storeTxt * readTemp(const char * filename) {
  FILE * f = readFile(filename);
  storeTxt * st = malloc(sizeof(*st));
  st->line = NULL;
  st->len = 0;
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    st->line = realloc(st->line, (st->len + 1) * sizeof(*st->line));
    st->line[st->len] = line;
    line = NULL;
    st->len++;
  }
  free(line);
  closeFile(f);
  return st;
}

//process the story template
void processTemp(storeTxt * st, catarray_t * carr, category_t * pre) {
  //for each line in st, replace the category name
  for (size_t i = 0; i < st->len; i++) {
    st->line[i] = repCName(st->line[i], carr, pre);
  }
}

//judge the category name, whether it is a positive number.
const char * judCName(char * name, catarray_t * carr, category_t * pre) {
  if (pre != NULL) {
    //if it is a positive number, return previous word if exists
    if (atoi(name) >= 1) {
      size_t index = pre->n_words - atoi(name);
      free(name);
      if (index < 1) {
        fprintf(stderr, "The backreference number is too big\n");
        exit(EXIT_FAILURE);
      }
      const char * word = pre->words[index];
      pre->n_words++;
      pre->words = realloc(pre->words, pre->n_words * sizeof(*pre->words));
      pre->words[pre->n_words - 1] = strdup(word);
      return word;
    }
  }
  // if not, return the word in carr
  const char * word = chooseWord(name, carr);
  pre->n_words++;
  pre->words = realloc(pre->words, pre->n_words * sizeof(*pre->words));
  pre->words[pre->n_words - 1] = strdup(word);
  free(name);
  return word;
}

//replace the category name with the word
char * repCName(char * line, catarray_t * carr, category_t * pre) {
  //check if there is _ sign on the line
  char * _1 = strchr(line, '_');
  if (_1 == NULL) {
    return line;
  }
  //check if there is a second _ sign on the same line
  char * _2 = strchr(_1 + 1, '_');
  if (_2 == NULL) {
    fprintf(stderr, "Incompete _ \n");
    exit(EXIT_FAILURE);
  }

  //record the category name's size
  size_t nameSZ = _2 - _1 - 1;
  //record the category name
  char * name = strndup(_1 + 1, nameSZ);
  const char * word = judCName(name, carr, pre);
  size_t wordSZ = strlen(word);
  size_t lineSZ = strlen(line);
  //determine the replaced lenth of line
  size_t resultSZ = lineSZ - nameSZ - 2 + wordSZ;
  //need one more position to put '\0'
  char * result = malloc((resultSZ + 1) * sizeof(*result));
  //initialize the result line
  memset(result, '\0', resultSZ + 1);
  //get the index for the first occurred blank
  size_t pos1 = _1 - line;
  //replace the characters before first blank
  for (size_t i = 0; i < pos1; i++) {
    result[i] = line[i];
  }
  //replace the blank with chosen word
  for (size_t i = pos1; i < pos1 + wordSZ; i++) {
    result[i] = word[i - pos1];
  }
  //replace the characters after the first blank
  for (size_t i = pos1 + wordSZ; i < resultSZ; i++) {
    result[i] = line[i - wordSZ + nameSZ + 2];
  }
  free(line);
  //return recursively to find whether there are more blanks after the firts blank
  return repCName(result, carr, pre);
}

//print each line stored in struct storeTxt
void printLine(storeTxt * st) {
  for (size_t i = 0; i < st->len; i++) {
    printf("%s", st->line[i]);
  }
}

//free the storeTxt
void freeST(storeTxt * st) {
  for (size_t i = 0; i < st->len; i++) {
    free(st->line[i]);
  }
  free(st->line);
  free(st);
}

catarray_t * storeline(char * line, catarray_t * carr) {
  //Find the colon in the line
  char * colon = strchr(line, ':');
  size_t cateLen = colon - line;
  if (colon == NULL || *(colon + 1) == '\n' || strchr(line, '\n') == NULL) {
    fprintf(stderr, "Incorrect format.\n");
    exit(EXIT_FAILURE);
  }
  //Find the length of the category name and create a pointer to point to the
  //duplicated category name cateName

  char * cateName = strndup(line, cateLen);
  char * newline = strchr(line, '\n');
  //Find the length of the word and create a pointer to point to the
  //duplicated word
  size_t wrdLen = newline - colon - 1;
  char * word = strndup(colon + 1, wrdLen);
  //check if there is a category name exist in catarray the same as cateName
  for (size_t i = 0; i < carr->n; i++) {
    if (strcmp(cateName, carr->arr[i].name) == 0) {
      carr->arr[i].n_words++;
      carr->arr[i].words =
          realloc(carr->arr[i].words, carr->arr[i].n_words * sizeof(*carr->arr[i].words));
      carr->arr[i].words[carr->arr[i].n_words - 1] = word;
      free(cateName);
      return carr;
    }
  }

  //if not exist such a category name in catarray, add
  //new category in catarray
  carr->n++;
  carr->arr = realloc(carr->arr, carr->n * sizeof(*carr->arr));
  category_t new;
  new.n_words = 1;
  new.name = cateName;
  new.words = malloc(new.n_words * sizeof(*new.words));
  new.words[new.n_words - 1] = word;
  carr->arr[carr->n - 1] = new;
  return carr;
}

//store categories and words into catarray_t
catarray_t * storeCat(storeTxt * st) {
  catarray_t * carr = malloc(sizeof(*carr));
  carr->arr = NULL;
  carr->n = 0;
  //iterate each line stored in st and return carr
  for (size_t i = 0; i < st->len; i++) {
    carr = storeline(st->line[i], carr);
  }
  return carr;
}

//free category_t
void freeCate(category_t * cate) {
  for (size_t i = 0; i < cate->n_words; i++) {
    free(cate->words[i]);
  }
  free(cate->words);
  free(cate->name);
}

//free catarray
void freeCarr(catarray_t * carr) {
  if (carr != NULL) {
    for (size_t i = 0; i < carr->n; i++) {
      freeCate(&carr->arr[i]);
    }
    if (carr->arr != NULL) {
      free(carr->arr);
    }
    free(carr);
  }
}
