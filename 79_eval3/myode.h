#ifndef MYODE_H
#define MYODE_H

#include <cassert>
#include <iostream>
#include <vector>
class MyOde {
 private:
  double m, c, k, a, om;

 public:
  MyOde(const std::vector<double> & params);
  std::vector<double> operator()(double t, const std::vector<double> & statVar) const;
  unsigned getOrder() const;

  friend std::ostream & operator<<(std::ostream & os, const MyOde & ode);
};
std::ostream & operator<<(std::ostream & os, const MyOde & ode);
#endif  // MYODE_H
