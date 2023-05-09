#include "euler.h"

#include <cmath>
//constructor
EulerSimulation::EulerSimulation(const MyOde & ode) : ode(new MyOde(ode)) {
}
//destructor
EulerSimulation::~EulerSimulation() {
  delete ode;
}
//ODE solution return a vector of time series and a vector of state variables as a pair
odesoln_t EulerSimulation::operator()(const std::vector<double> & tspan,
                                      const std::vector<double> & ics,
                                      size_t n) {
  assert(tspan.size() == 2);
  assert(ics.size() == 2);
  assert(n >= 1 && std::floor(n) == n);
  double dt = (tspan[1] - tspan[0]) / (n - 1);
  std::vector<double> t(n);
  std::vector<std::vector<double> > state(n, std::vector<double>(ics.size()));
  t[0] = tspan[0];
  state[0] = ics;

  for (size_t i = 1; i < n; i++) {
    t[i] = t[i - 1] + dt;
    std::vector<double> derivs = (*ode)(t[i - 1], state[i - 1]);
    for (size_t j = 0; j < ics.size(); ++j) {
      state[i][j] = state[i - 1][j] + dt * derivs[j];
    }
  }

  return std::make_pair(t, state);
}
//overloaded stream insertion operator
std::ostream & operator<<(std::ostream & os, const odesoln_t & soln) {
  for (size_t i = 0; i < soln.first.size(); ++i) {
    os << soln.first[i];
    for (size_t j = 0; j < soln.second[i].size(); ++j) {
      os << "," << soln.second[i][j];
    }
    os << std::endl;
  }
  return os;
}
