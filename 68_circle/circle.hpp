#include "point.hpp"

class Circle {
  Point center;
  const double radius;

 public:
  Circle(Point & center, const double radius);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
