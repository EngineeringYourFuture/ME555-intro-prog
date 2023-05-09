#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned true_ans = power(x, y);
  if (true_ans != expected_ans) {
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(0, 0, 1);
  run_check(0, 1, 0);
  run_check(1, 0, 1);
  run_check(123456, 1, 123456);
  run_check(3, 3, 27);
  run_check(4, 4, 256);
  return EXIT_SUCCESS;
}
