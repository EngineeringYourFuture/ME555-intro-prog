#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int findmax(int * arr) {
  int n = 26;
  int maxindex = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i] > arr[maxindex]) {
      maxindex = i;
    }
  }
  return maxindex;
}

int findkey(FILE * f) {
  int c;
  int arr[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      arr[c]++;
    }
  }

  int key = findmax(arr) - ('e' - 'a');
  if (key < 0) {
    key += 26;
  }
  return key;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  int key = findkey(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  if (key < 0 || key >= 26) {
    fprintf(stderr, "Invalid key\n");
    return EXIT_FAILURE;
  }
  fprintf(stdout, "%d\n", key);

  return EXIT_SUCCESS;
}
