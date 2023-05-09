#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long sqrt_t(int n) {
  if (n == 0 || n == 1) {
    return n;
  }
  long i = 1, result = 1;
  while (result <= n) {
    i++;
    result = i * i;
  }
  return i - 1;
}

int square_root(int x, int * perfect) {
  // WRITE ME
  if (x < 0) {
    *perfect = 0;
    return -1;
  }
  else if (x == sqrt_t(x) * sqrt_t(x)) {
    *perfect = 1;
    return sqrt_t(x);
  }
  else {
    *perfect = 0;
    return sqrt_t(x);
  }
}

/* helper function to call square_root and print whether the input is a 
   perfect square or not */
void test_one(int x) {
  int perfect;
  int rt = square_root(x, &perfect);
  if (perfect) {
    printf("sqrt(%d) is %d, perfect square\n", x, rt);
  }
  else {
    printf("sqrt(%d) is %d, NOT perfect square\n", x, rt);
  }
}

int main(void) {
  test_one(4);
  test_one(5);
  test_one(0);
  test_one(-1);
  test_one(-4);
  // test with the largest int that does not cause any operation in
  // square_root to overflow
  test_one(2147395600);
  // test with the one less than the largest int that does not cause
  // any operation in square_root to overflow
  test_one(2147395599);
  return EXIT_SUCCESS;
}
