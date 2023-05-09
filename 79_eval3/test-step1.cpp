#include <cassert>
#include <cstdlib>
#include <iostream>

#include "myode.h"
//test function exit error if error occurs
void test(const std::vector<double> & params,
          double t,
          const std::vector<double> & statVar,
          const std::vector<double> & expected) {
  assert(params.size() == 5);
  assert(statVar.size() == 2);
  MyOde ode(params);
  std::vector<double> result = ode(t, statVar);
  assert(result.size() == expected.size());
  for (size_t i = 0; i < result.size(); i++) {
    assert(std::abs(result[i] - expected[i]) < 1e-6);
  }
  std::cout << "Test passed for parameters: ";
  for (size_t i = 0; i < params.size(); i++) {
    std::cout << params[i] << " ";
  }
  std::cout << "\nODE: " << ode << std::endl;
}
int main() {
  double p1[] = {1, 0.1, 5, 2, 6};
  std::vector<double> params(p1, p1 + sizeof(p1) / sizeof(double));
  double t1 = 0;
  double statVar1[] = {0.5, 0};
  std::vector<double> statVar(statVar1, statVar1 + sizeof(statVar1) / sizeof(double));
  double expected1[] = {0, -2.5};
  std::vector<double> expected(expected1, expected1 + sizeof(expected1) / sizeof(double));
  test(params, t1, statVar, expected);
  return EXIT_SUCCESS;
}
