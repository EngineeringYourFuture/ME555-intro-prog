#ifndef __EXPR__H__
#define __EXPR__H__
#include <cstdlib>
#include <sstream>
#include <string>
class Expression {
 public:
  Expression(){};
  virtual std::string toString() const = 0;
  virtual ~Expression(){};
};
class NumExpression : public Expression {
 private:
  long number;

 public:
  NumExpression(long num) : number(num){};
  virtual std::string toString() const {
    std::stringstream ss;
    ss << number;
    return ss.str();
  }
  virtual ~NumExpression(){};
};
class PlusExpression : public Expression {
 private:
  Expression * l;
  Expression * r;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << l->toString() << " + " << r->toString() << ")";
    return ss.str();
  }
  virtual ~PlusExpression() {
    delete l;
    delete r;
  }
};
#endif
