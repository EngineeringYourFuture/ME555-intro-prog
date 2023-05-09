#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double cal_balance(retire_info info, double balance, int startAge) {
  for (int i = 0; i < info.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, balance);
    balance = balance * (info.rate_of_return / 12) + balance + info.contribution;
    startAge += 1;
  }
  return balance;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double worked = cal_balance(working, initial, startAge);
  cal_balance(retired, worked, startAge + working.months);
}

int main() {
  retire_info working = {489, 1000, 0.045};
  retire_info retired = {384, -4000, 0.01};
  retirement(327, 21345, working, retired);
  return 0;
}
