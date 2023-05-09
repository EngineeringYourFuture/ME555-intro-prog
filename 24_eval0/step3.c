#include <stdio.h>
#include <stdlib.h>
//Write function for seq3
int seq3(int x, int y) {
  return (y + 4) * (x - 1) + 3;
}

//Wirte function for count_neg_seq3_range
int count_neg_seq3_range(int xLow, int xHi, int yLow, int yHi) {
  int count = 0;
  if (xLow <= xHi && yLow <= yHi) {
    for (int i = xLow; i < xHi; i++) {
      for (int j = yLow; j < yHi; j++) {
        if (seq3(i, j) < 0) {
          count += 1;
        }
      }
    }
  }
  return count;
}

//Write test cases in main
int main(void) {
  int x1 = -8, x2 = -4, x3 = -2, x4 = 4, x5 = 0, y1 = 0, y2 = 2, y3 = 4, y4 = -1, y5 = -2;
  printf("seq3(%d, %d) = %d\n", x1, y1, seq3(x1, y1));
  printf("seq3(%d, %d) = %d\n", x1, y2, seq3(x1, y2));
  printf("seq3(%d, %d) = %d\n", x1, y3, seq3(x1, y3));
  printf("seq3(%d, %d) = %d\n", x2, y1, seq3(x2, y1));
  printf("seq3(%d, %d) = %d\n", x2, y2, seq3(x2, y2));
  printf("seq3(%d, %d) = %d\n", x2, y3, seq3(x2, y3));
  printf("seq3(%d, %d) = %d\n", x3, y1, seq3(x3, y1));
  printf("seq3(%d, %d) = %d\n", x3, y2, seq3(x3, y2));
  printf("seq3(%d, %d) = %d\n", x3, y3, seq3(x3, y3));
  printf("seq3(%d, %d) = %d\n", x4, y4, seq3(x4, y4));
  printf("seq3(%d, %d) = %d\n", x4, y3, seq3(x4, y3));
  printf("seq3(%d, %d) = %d\n", x1, y4, seq3(x1, y4));
  printf("seq3(%d, %d) = %d\n", x5, y4, seq3(x5, y4));
  printf("seq3(%d, %d) = %d\n", x2, y4, seq3(x2, y4));
  printf("seq3(%d, %d) = %d\n", x4, y5, seq3(x4, y5));
  printf("seq3(%d, %d) = %d\n", x4, y2, seq3(x4, y2));
  printf("seq3(%d, %d) = %d\n", x1, y5, seq3(x1, y5));

  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         x1,
         x2,
         y1,
         y2,
         count_neg_seq3_range(x1, x2, y1, y2));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         x1,
         x3,
         y1,
         y3,
         count_neg_seq3_range(x1, x3, y1, y3));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         x2,
         x3,
         y2,
         y3,
         count_neg_seq3_range(x2, x3, y2, y3));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         x3,
         x3,
         y3,
         y3,
         count_neg_seq3_range(x3, x3, y3, y3));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         x3,
         x1,
         y3,
         y1,
         count_neg_seq3_range(x3, x1, y3, y1));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         x5,
         x5,
         y1,
         y1,
         count_neg_seq3_range(x5, x5, y1, y1));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         0,
         5,
         0,
         5,
         count_neg_seq3_range(0, 5, 0, 5));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         -5,
         5,
         -5,
         5,
         count_neg_seq3_range(-5, 5, -5, 5));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         0,
         5,
         -5,
         5,
         count_neg_seq3_range(0, 5, -5, 5));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         -5,
         0,
         0,
         5,
         count_neg_seq3_range(-5, 0, 0, 5));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         -10,
         -5,
         5,
         10,
         count_neg_seq3_range(-10, -5, 5, 10));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         5,
         0,
         0,
         5,
         count_neg_seq3_range(5, 0, 0, 5));
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         0,
         5,
         5,
         0,
         count_neg_seq3_range(0, 5, 5, 0));
  return EXIT_SUCCESS;
}
