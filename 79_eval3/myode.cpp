#include "myode.h"

#include <cmath>
//constructor
MyOde::MyOde(const std::vector<double> & params) :

    m(params[0]), c(params[1]), k(params[2]), a(params[3]), om(params[4]) {
  assert(params.size() == 5);
}
//function operator
std::vector<double> MyOde::operator()(double t,
                                      const std::vector<double> & statVar) const {
  assert(statVar.size() == 2);
  std::vector<double> ydot(2);
  ydot[0] = statVar[1];
  ydot[1] = (a * std::sin(om * t) - c * statVar[1] - k * statVar[0]) / m;
  return ydot;
}

unsigned MyOde::getOrder() const {
  return 2;
}
//overloaded the stream insertion operator
std::ostream & operator<<(std::ostream & os, const MyOde & ode) {
  os << ode.m << "*xddot + " << ode.c << "*xdot + " << ode.k << "*x = " << ode.a
     << "*sin(" << ode.om << "*t)";
  return os;
}
