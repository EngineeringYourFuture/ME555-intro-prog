#include <stdio.h>
#include <stdlib.h>
#define LINE_SIZE 10

void rotateMatrix(FILE * f) {
  char matrix[LINE_SIZE][LINE_SIZE];
  char line[LINE_SIZE + 2];
  int num_line = 0;
  while (fgets(line, LINE_SIZE + 2, f) != NULL) {
    num_line++;
    if (line[10] != '\n') {
      fprintf(stderr, "Incorrect # characters on line %d\n", num_line);
      exit(EXIT_FAILURE);
    }
    if (num_line > 10) {
      fprintf(stderr, "Too many lines\n");
      exit(EXIT_FAILURE);
    }
    for (int i = 0; i < LINE_SIZE; i++) {
      matrix[i][LINE_SIZE - num_line] = line[i];
    }
  }
  if (num_line < 10) {
    fprintf(stderr, "Not enough lines\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < LINE_SIZE; i++) {
    for (int j = 0; j < LINE_SIZE; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Invalid # arguments\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  rotateMatrix(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
