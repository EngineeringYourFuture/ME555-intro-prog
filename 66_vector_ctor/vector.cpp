#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
/*void Vector2D::initVector(double init_x, double init_y) {
  x = init_x;
  y = init_y;
}*/
Vector2D::Vector2D() : x(0.0), y(0.0) {
}
Vector2D::Vector2D(double x, double y) : x(x), y(y) {
}
double Vector2D::getMagnitude() const {
  return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}
Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D new_vec;
  new_vec.x = x + rhs.x;
  new_vec.y = y + rhs.y;
  return new_vec;
}
Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}
double Vector2D::dot(const Vector2D & rhs) const {
  return x * rhs.x + y * rhs.y;
}
void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}
