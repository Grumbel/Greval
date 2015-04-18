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
  virtual void accept(Visitor& visitor) const = 0;
};

class UnaryOp : public Expr
{
protected:
  std::unique_ptr<Expr> m_rhs;

public:
  const Expr& get_rhs() const { return *m_rhs; }

  UnaryOp(std::unique_ptr<Expr>&& rhs) :
    m_rhs(std::move(rhs))
  {}
};

class BinaryOp : public Expr
{
protected:
  std::unique_ptr<Expr> m_lhs;
  std::unique_ptr<Expr> m_rhs;

public:
  const Expr& get_lhs() const { return *m_lhs; }
  const Expr& get_rhs() const { return *m_rhs; }

  BinaryOp(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    m_lhs(std::move(lhs)),
    m_rhs(std::move(rhs))
  {}
};

class Plus : public BinaryOp
{
public:
  Plus(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};

class Minus : public BinaryOp
{
public:
  Minus(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};

class Mult : public BinaryOp
{
public:
  Mult(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};

class Div : public BinaryOp
{
public:
  Div(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};

class Modulo : public BinaryOp
{
public:
  Modulo(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};

class BitwiseAND : public BinaryOp
{
public:
  BitwiseAND(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};

class BitwiseXOR : public BinaryOp
{
public:
  BitwiseXOR(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};

class BitwiseOR : public BinaryOp
{
public:
  BitwiseOR(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};

class Equal : public BinaryOp
{
public:
  Equal(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};

class NotEqual : public BinaryOp
{
public:
  NotEqual(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};

class LargerThen : public BinaryOp
{
public:
  LargerThen(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};

class SmallerThen : public BinaryOp
{
public:
  SmallerThen(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};

class SmallerOrEqualThen : public BinaryOp
{
public:
  SmallerOrEqualThen(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};

class LargerOrEqualThen : public BinaryOp
{
public:
  LargerOrEqualThen(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};


class ShiftLeft : public BinaryOp
{
public:
  ShiftLeft(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};

class ShiftRight : public BinaryOp
{
public:
  ShiftRight(std::unique_ptr<Expr>&& lhs, std::unique_ptr<Expr>&& rhs) :
    BinaryOp(std::move(lhs), std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_lhs, *m_rhs); }
};

class LogicalNOT : public UnaryOp
{
public:
  LogicalNOT(std::unique_ptr<Expr>&& rhs) :
    UnaryOp(std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_rhs); }
};

class BitwiseNOT : public UnaryOp
{
public:
  BitwiseNOT(std::unique_ptr<Expr>&& rhs) :
    UnaryOp(std::move(rhs))
  {}

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_rhs); }
};

class Negate : public UnaryOp
{
public:
  Negate(std::unique_ptr<Expr>&& rhs) :
    UnaryOp(std::move(rhs))
  {}

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

  void accept(Visitor& visitor) const { visitor.visit(*this, *m_expr, *m_lhs, *m_rhs); }
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

  void accept(Visitor& visitor) const { visitor.visit(*this); }
};

class Integer : public Expr
{
  int m_value;

public:
  Integer(int value) :
    m_value(value)
  {}

  int get_value() const { return m_value; }

  void accept(Visitor& visitor) const { visitor.visit(*this); }
};

class Real : public Expr
{
  float m_value;

public:
  Real(float value) :
    m_value(value)
  {}

  float get_value() const { return m_value; }

  void accept(Visitor& visitor) const { visitor.visit(*this); }
};

#endif

/* EOF */
