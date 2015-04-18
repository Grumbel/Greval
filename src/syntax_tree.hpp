// Expr - A simple toy programming language
// Copyright (C) 2011 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_SYNTAX_TREE_HPP
#define HEADER_SYNTAX_TREE_HPP

#include <ostream>
#include <memory>
#include <vector>

#include "value.hpp"
#include "environment.hpp"
#include "visitor.hpp"

class Visitor;

class Expr
{
public:
  virtual ~Expr() {}
  virtual Value eval(const Environment& env) const = 0;

  virtual void accept(Visitor& visitor) const = 0;
};

class Plus : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  Plus(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) + m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  Plus(const Plus&);
  Plus& operator=(const Plus&);
};

class Minus : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  Minus(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) - m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  Minus(const Minus&);
  Minus& operator=(const Minus&);
};

class Mult : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  Mult(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) * m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  Mult(const Mult&);
  Mult& operator=(const Mult&);
};

class Div : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  Div(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) / m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  Div(const Div&);
  Div& operator=(const Div&);
};

class Modulo : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  Modulo(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) % m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  Modulo(const Modulo&);
  Modulo& operator=(const Modulo&);
};

class BitwiseAND : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  BitwiseAND(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) & m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  BitwiseAND(const BitwiseAND&);
  BitwiseAND& operator=(const BitwiseAND&);
};

class BitwiseXOR : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  BitwiseXOR(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) ^ m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  BitwiseXOR(const BitwiseXOR&);
  BitwiseXOR& operator=(const BitwiseXOR&);
};

class BitwiseOR : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  BitwiseOR(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) | m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  BitwiseOR(const BitwiseOR&);
  BitwiseOR& operator=(const BitwiseOR&);
};

class Equal : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  Equal(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) == m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  Equal(const Equal&);
  Equal& operator=(const Equal&);
};

class NotEqual : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  NotEqual(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) != m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  NotEqual(const NotEqual&);
  NotEqual& operator=(const NotEqual&);
};

class LargerThen : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  LargerThen(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) > m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  LargerThen(const LargerThen&);
  LargerThen& operator=(const LargerThen&);
};

class SmallerThen : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  SmallerThen(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) < m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  SmallerThen(const SmallerThen&);
  SmallerThen& operator=(const SmallerThen&);
};

class SmallerOrEqualThen : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  SmallerOrEqualThen(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) <= m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  SmallerOrEqualThen(const SmallerOrEqualThen&);
  SmallerOrEqualThen& operator=(const SmallerOrEqualThen&);
};

class LargerOrEqualThen : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  LargerOrEqualThen(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) >= m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  LargerOrEqualThen(const LargerOrEqualThen&);
  LargerOrEqualThen& operator=(const LargerOrEqualThen&);
};


class ShiftLeft : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  ShiftLeft(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) << m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  ShiftLeft(const ShiftLeft&);
  ShiftLeft& operator=(const ShiftLeft&);
};

class ShiftRight : public Expr
{
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  ShiftRight(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return m_lhs->eval(env) >> m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }

private:
  ShiftRight(const ShiftRight&);
  ShiftRight& operator=(const ShiftRight&);
};

class LogicalNOT : public Expr
{
private:
  std::unique_ptr<Expr> m_rhs;

public:
  LogicalNOT(std::unique_ptr<Expr>&& rhs) :
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return !m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_rhs); }
};

class BitwiseNOT : public Expr
{
private:
  std::unique_ptr<Expr> m_rhs;

public:
  BitwiseNOT(std::unique_ptr<Expr>&& rhs) :
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    return ~m_rhs->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_rhs); }
};


class Condition : public Expr
{
  std::unique_ptr<Expr> m_expr;
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  Condition(std::unique_ptr<Expr>&& expr, std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_expr(std::move(expr)),
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}

  Value eval(const Environment& env) const
  {
    if (m_expr->eval(env))
    {
      return m_lhs->eval(env);
    }
    else
    {
      return m_rhs->eval(env);
    }
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_expr, *m_lhs, *m_rhs); }
};

class Negate : public Expr
{
private:
  std::unique_ptr<Expr> m_expr;

public:
  Negate(std::unique_ptr<Expr>&& expr) :
    m_expr(std::move(expr))
  {}

  Value eval(const Environment& env) const
  {
    return -m_expr->eval(env);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_expr); }
};

class Function : public Expr
{
private:
  std::string m_name;
  std::vector<std::unique_ptr<Expr> > m_args;

public:
  Function(const std::string& name, std::vector<std::unique_ptr<Expr> >&& args) :
    m_name(name),
    m_args(std::move(args))
  {}

  std::string get_name() const { return m_name; }
  const std::vector<std::unique_ptr<Expr> >& get_args() const { return m_args; }

  Value eval(const Environment& env) const
  {
    std::vector<Value> values;
    for(auto i = m_args.begin(); i != m_args.end(); ++i)
    {
      values.push_back((*i)->eval(env));
    }
    return env.lookup_function(m_name)(values);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this); }
};

class Variable : public Expr
{
private:
  std::string m_name;

public:
  Variable(const std::string& name) :
    m_name(name)
  {}

  std::string get_name() const { return m_name; }

  Value eval(const Environment& env) const
  {
    return env.lookup_variable(m_name);
  }

  void accept(Visitor& visitor) const { visitor.visit(*this); }
};

class Integer : public Expr
{
  int m_value;

public:
  Integer(int value) :
    m_value(value)
  {}

  Value eval(const Environment& env) const
  {
    return Value::integer(m_value);
  }

  int get_value() const { return m_value; }

  void accept(Visitor& visitor) const { visitor.visit(*this); }

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

  Value eval(const Environment& env) const
  {
    return Value::real(m_value);
  }

  float get_value() const { return m_value; }

  void accept(Visitor& visitor) const { visitor.visit(*this); }

private:
  Real(const Real&);
  Real& operator=(const Real&);
};

#endif

/* EOF */
