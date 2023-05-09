#ifndef __EXPR__H__
#define __EXPR__H__
#include <cstdlib>
#include <sstream>
#include <string>

class Expression {
 public:
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
//a class that the child class shares the field, constructor and destructor.
class ShareExpre : public Expression {
 private:
  Expression * l;
  Expression * r;
  const char * op;  //the operator character
 public:
  ShareExpre(const char * oper, Expression * lhs, Expression * rhs) :
      l(lhs), r(rhs), op(oper) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << l->toString() << " " << op << " " << r->toString() << ")";
    return ss.str();
  }
  virtual ~ShareExpre() {
    delete l;
    delete r;
  }
};
class PlusExpression : public ShareExpre {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : ShareExpre("+", lhs, rhs) {}
};
class MinusExpression : public ShareExpre {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : ShareExpre("-", lhs, rhs) {}
};
class TimesExpression : public ShareExpre {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : ShareExpre("*", lhs, rhs) {}
};
class DivExpression : public ShareExpre {
 public:
  DivExpression(Expression * lhs, Expression * rhs) : ShareExpre("/", lhs, rhs) {}
};
#endif
