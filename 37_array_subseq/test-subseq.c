#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int run_check(int * array, size_t n, size_t c_ans) {
  size_t ans = maxSeq(array, n);
  if (ans == c_ans) {
    printf("pass\n");
    return EXIT_SUCCESS;
  }
  else {
    printf("fail\n");
    exit(EXIT_FAILURE);
  }
}

int main() {
  int array0[0];
  int array1[1] = {0};
  int array2[2] = {-1, 0};
  int array3[3] = {3, 2, 1};
  int array4[4] = {-4, -3, -2, -1};
  int array5[5] = {1, 1, 1, 1, 1};
  int array6[6] = {0};
  int array7[7] = {1, 1, 1, 3, 5, 8, 1};
  int array8[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  int array9[9] = {2};
  int array10[10] = {1, 2, 1, 3, 5, 8, 2, 4, 6, 9};
  int array11[11] = {1, 2, 3, 1, 2, 3, 4, 5, 1, 2, 3};
  run_check(array0, 0, 0);
  run_check(array1, 1, 1);
  run_check(array2, 2, 2);
  run_check(array3, 3, 1);
  run_check(array4, 4, 4);
  run_check(array5, 5, 1);
  run_check(array6, 6, 1);
  run_check(array7, 7, 4);
  run_check(array8, 8, 8);
  run_check(array9, 9, 1);
  run_check(array10, 10, 4);
  run_check(array11, 11, 5);
  return 0;
}
