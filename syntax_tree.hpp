#ifndef HEADER_SYNTAX_TREE_HPP
#define HEADER_SYNTAX_TREE_HPP

#include <boost/scoped_ptr.hpp>

class Expr
{
public:
  virtual ~Expr() {}
  virtual float eval() const =0;
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

  float eval() const
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

  float eval() const
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

  float eval() const
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

  float eval() const
  {
    return m_lhs->eval() / m_rhs->eval();
  }

private:
  Div(const Div&);
  Div& operator=(const Div&);
};

class Integer : public Expr
{
  int m_value;

public:
  Integer(int value) :
    m_value(value)
  {}

  float eval() const
  {
    return static_cast<float>(m_value);
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

  float eval() const
  {
    return m_value;
  }

private:
  Real(const Real&);
  Real& operator=(const Real&);
};

#endif

/* EOF */
