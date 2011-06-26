#ifndef HEADER_SYNTAX_TREE_HPP
#define HEADER_SYNTAX_TREE_HPP

#include <boost/scoped_ptr.hpp>

#include "value.hpp"

class Expr
{
public:
  virtual ~Expr() {}
  virtual Value eval() const =0;
};

class Plus : public Expr
{
  boost::scoped_ptr<Expr> m_lhs;
  boost::scoped_ptr<Expr> m_rhs;

public:
  Plus(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), 
    m_rhs(rhs)
  {}

  Value eval() const
  {
    return m_lhs->eval() + m_rhs->eval();
  }

private:
  Plus(const Plus&);
  Plus& operator=(const Plus&);
};

class Minus : public Expr
{
  boost::scoped_ptr<Expr> m_lhs;
  boost::scoped_ptr<Expr> m_rhs;

public:
  Minus(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), 
    m_rhs(rhs)
  {}

  Value eval() const
  {
    return m_lhs->eval() - m_rhs->eval();
  }

private:
  Minus(const Minus&);
  Minus& operator=(const Minus&);
};

class Mult : public Expr
{
  boost::scoped_ptr<Expr> m_lhs;
  boost::scoped_ptr<Expr> m_rhs;

public:
  Mult(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), 
    m_rhs(rhs)
  {}

  Value eval() const
  {
    return m_lhs->eval() * m_rhs->eval();
  }

private:
  Mult(const Mult&);
  Mult& operator=(const Mult&);
};

class Div : public Expr
{
  boost::scoped_ptr<Expr> m_lhs;
  boost::scoped_ptr<Expr> m_rhs;

public:
  Div(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), 
    m_rhs(rhs)
  {}

  Value eval() const
  {
    return m_lhs->eval() / m_rhs->eval();
  }

private:
  Div(const Div&);
  Div& operator=(const Div&);
};

class Modulo : public Expr
{
  boost::scoped_ptr<Expr> m_lhs;
  boost::scoped_ptr<Expr> m_rhs;

public:
  Modulo(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), 
    m_rhs(rhs)
  {}

  Value eval() const
  {
    return m_lhs->eval() % m_rhs->eval();
  }

private:
  Modulo(const Modulo&);
  Modulo& operator=(const Modulo&);
};

class LargerThen : public Expr
{
  boost::scoped_ptr<Expr> m_lhs;
  boost::scoped_ptr<Expr> m_rhs;

public:
  LargerThen(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), 
    m_rhs(rhs)
  {}

  Value eval() const
  {
    return m_lhs->eval() > m_rhs->eval();
  }

private:
  LargerThen(const LargerThen&);
  LargerThen& operator=(const LargerThen&);
};

class SmallerThen : public Expr
{
  boost::scoped_ptr<Expr> m_lhs;
  boost::scoped_ptr<Expr> m_rhs;

public:
  SmallerThen(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), 
    m_rhs(rhs)
  {}

  Value eval() const
  {
    return m_lhs->eval() < m_rhs->eval();
  }

private:
  SmallerThen(const SmallerThen&);
  SmallerThen& operator=(const SmallerThen&);
};

class SmallerOrEqualThen : public Expr
{
  boost::scoped_ptr<Expr> m_lhs;
  boost::scoped_ptr<Expr> m_rhs;

public:
  SmallerOrEqualThen(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), 
    m_rhs(rhs)
  {}

  Value eval() const
  {
    return m_lhs->eval() <= m_rhs->eval();
  }

private:
  SmallerOrEqualThen(const SmallerOrEqualThen&);
  SmallerOrEqualThen& operator=(const SmallerOrEqualThen&);
};

class LargerOrEqualThen : public Expr
{
  boost::scoped_ptr<Expr> m_lhs;
  boost::scoped_ptr<Expr> m_rhs;

public:
  LargerOrEqualThen(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), 
    m_rhs(rhs)
  {}

  Value eval() const
  {
    return m_lhs->eval() >= m_rhs->eval();
  }

private:
  LargerOrEqualThen(const LargerOrEqualThen&);
  LargerOrEqualThen& operator=(const LargerOrEqualThen&);
};


class ShiftLeft : public Expr
{
  boost::scoped_ptr<Expr> m_lhs;
  boost::scoped_ptr<Expr> m_rhs;

public:
  ShiftLeft(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), 
    m_rhs(rhs)
  {}

  Value eval() const
  {
    return m_lhs->eval() << m_rhs->eval();
  }

private:
  ShiftLeft(const ShiftLeft&);
  ShiftLeft& operator=(const ShiftLeft&);
};

class ShiftRight : public Expr
{
  boost::scoped_ptr<Expr> m_lhs;
  boost::scoped_ptr<Expr> m_rhs;

public:
  ShiftRight(Expr* lhs, Expr* rhs) :
    m_lhs(lhs), 
    m_rhs(rhs)
  {}

  Value eval() const
  {
    return m_lhs->eval() >> m_rhs->eval();
  }

private:
  ShiftRight(const ShiftRight&);
  ShiftRight& operator=(const ShiftRight&);
};

class LogicalNOT : public Expr
{
private:
  boost::scoped_ptr<Expr> m_rhs;

public:
  LogicalNOT(Expr* rhs) :
    m_rhs(rhs)
  {}

  Value eval() const
  {
    return !m_rhs->eval();
  }
};

class BitwiseNOT : public Expr
{
private:
  boost::scoped_ptr<Expr> m_rhs;

public:
  BitwiseNOT(Expr* rhs) :
    m_rhs(rhs)
  {}

  Value eval() const
  {
    return ~m_rhs->eval();
  }
};

class Integer : public Expr
{
  int m_value;

public:
  Integer(int value) :
    m_value(value)
  {}

  Value eval() const
  {
    return Value::integer(m_value);
  }

private:
  Integer(const Integer&);
  Integer& operator=(const Integer&);
};

class Real : public Expr
{
  float m_value;

public:
  Real(float value) :
    m_value(value)
  {}

  Value eval() const
  {
    return Value::real(m_value);
  }

private:
  Real(const Real&);
  Real& operator=(const Real&);
};

#endif

/* EOF */
