#include <stdio.h>
#include <stdlib.h>
//Write function for seq2
int seq2(int x) {
  return -2 + (x - 2) * (x - 2);
}

//Wirte function for sum_seq2
int sum_seq2(int low, int high) {
  int result = 0;
  if (high > low) {
    for (int i = low; i < high; i++) {
      result += seq2(i);
    }
    return result;
  }
  else {
    return 0;
  }
}

//Write test cases in main
int main(void) {
  int x1 = -4, x2 = -5, x3 = -6, x4 = 0, x5 = 3;
  ;
  printf("seq2(%d) = %d\n", x1, seq2(x1));
  printf("seq2(%d) = %d\n", x2, seq2(x2));
  printf("seq2(%d) = %d\n", x3, seq2(x3));
  printf("seq2(%d) = %d\n", x4, seq2(x4));
  printf("seq2(%d) = %d\n", x5, seq2(x5));
  printf("sum_seq2(%d, %d) = %d\n", x1, x2, sum_seq2(x1, x2));
  printf("sum_seq2(%d, %d) = %d\n", x1, x3, sum_seq2(x1, x3));
  printf("sum_seq2(%d, %d) = %d\n", x2, x2, sum_seq2(x2, x2));
  printf("sum_seq2(%d, %d) = %d\n", x2, x3, sum_seq2(x2, x3));
  printf("sum_seq2(%d, %d) = %d\n", x3, x2, sum_seq2(x3, x2));
  printf("sum_seq2(%d, %d) = %d\n", x1, x5, sum_seq2(x1, x5));
  return EXIT_SUCCESS;
}
