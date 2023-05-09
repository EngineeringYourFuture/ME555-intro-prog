#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  int count = 1, temp = 1;
  if (n == 0) {
    return 0;
  }
  for (size_t i = 1; i < n; i++) {
    if (array[i - 1] < array[i]) {
      count++;
      continue;
    }
    else {
      if (temp <= count)
        temp = count;
    }
    count = 1;
  }
  if (temp <= count) {
    temp = count;
  }
  return temp;
}
