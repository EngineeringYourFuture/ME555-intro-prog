#ifndef EULER_H
#define EULER_H

#include "myode.h"

typedef std::pair<std::vector<double>, std::vector<std::vector<double> > > odesoln_t;
class EulerSimulation {
 private:
  MyOde * ode;

 public:
  EulerSimulation(const MyOde & ode);
  ~EulerSimulation();

  odesoln_t operator()(const std::vector<double> & tspan,
                       const std::vector<double> & ics,
                       size_t n);

  friend void testEuler(EulerSimulation & es);
  friend std::ostream & operator<<(std::ostream & os, const odesoln_t & soln);
};

std::ostream & operator<<(std::ostream & os, const odesoln_t & soln);

#endif  // EULER_H
