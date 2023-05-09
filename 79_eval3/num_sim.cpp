#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <sstream>

#include "euler.h"
#include "myode.h"
//parse the arguments and convert them into numbers and exit with error if
//they are invalid arguments
std::vector<double> parse_input(const std::string & input) {
  std::vector<double> result;
  std::istringstream iss(input);
  std::string token;
  while (getline(iss, token, ',')) {
    char * end;
    double value = std::strtod(token.c_str(), &end);
    if (end != token.c_str() + token.length()) {
      std::cerr << "Invalid input: " << token << std::endl;
      exit(EXIT_FAILURE);
    }
    result.push_back(value);
  }
  return result;
}

int main(int argc, char ** argv) {
  if (argc != 5) {
    std::cerr << "wrong # arguments" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::vector<double> params = parse_input(argv[1]);
  assert(params.size() == 5);
  std::vector<double> tspan = parse_input(argv[2]);
  assert(tspan.size() == 2);
  std::vector<double> ics = parse_input(argv[3]);
  assert(ics.size() == 2);
  //convert the last argument into positive integer, exit error if it is not.
  char * end;
  double n_double = std::strtod(argv[4], &end);
  if (end != argv[4] + std::strlen(argv[4]) || n_double < 1 ||
      std::floor(n_double) != n_double) {
    std::cerr << "Invalid input for n: " << argv[4] << std::endl;
    exit(EXIT_FAILURE);
  }
  size_t n = n_double;
  MyOde ode(params);
  EulerSimulation es(ode);
  odesoln_t soln = es(tspan, ics, n);
  std::cout << soln;
  return EXIT_SUCCESS;
}
