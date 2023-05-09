#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "euler.h"

int main() {
  double p1[] = {1, 0.1, 5, 2, 6};
  std::vector<double> params(p1, p1 + sizeof(p1) / sizeof(double));
  //number of parameters should be 5
  assert(params.size() == 5);
  MyOde ode(params);
  EulerSimulation es(ode);
  double tspan1[] = {0, 1};
  std::vector<double> tspan(tspan1, tspan1 + sizeof(tspan1) / sizeof(double));
  //number of time span vector should be 2
  assert(tspan.size() == 2);

  double ics1[] = {0, 0.1};
  std::vector<double> ics(ics1, ics1 + sizeof(ics1) / sizeof(double));
  size_t n1 = 3;
  assert(ics.size() == 2 && std::floor(n1) == n1 && n1 > 1);
  odesoln_t soln = es(tspan, ics, n1);
  std::cout << "EulerSimulation results:\n" << soln;

  return EXIT_SUCCESS;
}
