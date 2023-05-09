#include "circle.hpp"

#include <cmath>
#define pi acos(-1.0)

Circle::Circle(Point & center, double radius) : center(center), radius(radius) {
}
void Circle::move(double dx, double dy) {
  center.Point::move(dx, dy);
}
double Circle::intersectionArea(const Circle & otherCircle) {
  double d = center.Point::distanceFrom(otherCircle.center);
  if (radius + otherCircle.radius <= d) {
    return 0;
  }
  else {
    if ((radius - d) >= otherCircle.radius) {
      return pi * std::pow(otherCircle.radius, 2);
    }
    if ((otherCircle.radius - d) >= radius) {
      return pi * std::pow(radius, 2);
    }
    if (otherCircle.radius - radius >= 0) {
      double ang1 =
          acos((radius * radius + d * d - otherCircle.radius * otherCircle.radius) /
               (2 * radius * d));
      double ang2 =
          acos((otherCircle.radius * otherCircle.radius + d * d - radius * radius) /
               (2 * otherCircle.radius * d));
      return ang1 * radius * radius + ang2 * otherCircle.radius * otherCircle.radius -
             radius * d * sin(ang1);
    }
    double ang1 =
        acos((otherCircle.radius * otherCircle.radius + d * d - radius * radius) /
             (2 * otherCircle.radius * d));
    double ang2 =
        acos((radius * radius + d * d - otherCircle.radius * otherCircle.radius) /
             (2 * radius * d));
    return ang1 * otherCircle.radius * otherCircle.radius + ang2 * radius * radius -
           otherCircle.radius * d * sin(ang1);
  }
}
