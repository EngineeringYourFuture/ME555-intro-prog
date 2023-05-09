#include <stdio.h>
#include <stdlib.h>
//Write function for seq1
int seq1(int x) {
  return x * 3 - 5;
}

//Wirte function for print_seq1_range
void print_seq1_range(int low, int high) {
  if (low < high) {
    for (int i = low; i < high - 1; i++) {
      printf("%d, ", seq1(i));
    }
    printf("%d\n", seq1(high - 1));
  }
  else {
    printf("\n");
  }
}

//Write test cases in main
int main(void) {
  int x1 = -4, x2 = -5, x3 = 8, x4 = 9, x5 = 10;
  printf("seq1(%d)=%d\n", x1, seq1(x1));
  printf("seq1(%d)=%d\n", x2, seq1(x2));
  printf("seq1(%d)=%d\n", x3, seq1(x3));
  printf("seq1(%d)=%d\n", x4, seq1(x4));
  printf("seq1(%d)=%d\n", x5, seq1(x5));
  printf("print_seq1_range(%d, %d)\n", x1, x2);
  print_seq1_range(x1, x2);
  printf("print_seq1_range(%d, %d)\n", x1, x3);
  print_seq1_range(x1, x3);
  printf("print_seq1_range(%d, %d)\n", x1, x4);
  print_seq1_range(x1, x4);
  printf("print_seq1_range(%d, %d)\n", x1, x5);
  print_seq1_range(x1, x5);
  printf("print_seq1_range(%d, %d)\n", x2, x2);
  print_seq1_range(x2, x2);
  printf("print_seq1_range(%d, %d)\n", x1, x5);
  print_seq1_range(x1, x5);
  return EXIT_SUCCESS;
}
