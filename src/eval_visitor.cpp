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

#include "eval_visitor.hpp"

#include <assert.h>

#include "environment.hpp"
#include "syntax_tree.hpp"

EvalVisitor::EvalVisitor(const Environment& env) :
  m_stack(),
  m_env(env)
{
}

Value
EvalVisitor::get_result() const
{
  assert(m_stack.size() == 1);
  return m_stack.back();
}

#define EVAL_BINARY_OP(op, lhs, rhs) \
  lhs.accept(*this); \
  assert(!m_stack.empty()); \
  Value lhs_value = m_stack.back(); \
  m_stack.pop_back(); \
  \
  rhs.accept(*this); \
  assert(!m_stack.empty()); \
  Value rhs_value = m_stack.back(); \
  m_stack.pop_back(); \
  \
  m_stack.push_back(lhs_value op rhs_value)

#define EVAL_UNARY_OP(op, rhs) \
  rhs.accept(*this); \
  assert(!m_stack.empty()); \
  Value rhs_value = m_stack.back(); \
  m_stack.pop_back(); \
  \
  m_stack.push_back(op rhs_value)

void
EvalVisitor::visit(const Plus& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(+, lhs, rhs);
}

void
EvalVisitor::visit(const Minus& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(-, lhs, rhs);
}

void
EvalVisitor::visit(const Mult& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(*, lhs, rhs);
}

void
EvalVisitor::visit(const Div& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(/, lhs, rhs);
}

void
EvalVisitor::visit(const Modulo& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(%, lhs, rhs);
}

void
EvalVisitor::visit(const BitwiseAND& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(&, lhs, rhs);
}

void
EvalVisitor::visit(const BitwiseXOR& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(^, lhs, rhs);
}

void
EvalVisitor::visit(const BitwiseOR& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(|, lhs, rhs);
}

void
EvalVisitor::visit(const Equal& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(==, lhs, rhs);
}

void
EvalVisitor::visit(const NotEqual& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(!=, lhs, rhs);
}

void
EvalVisitor::visit(const LargerThen& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(>, lhs, rhs);
}

void
EvalVisitor::visit(const SmallerThen& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(<, lhs, rhs);
}

void
EvalVisitor::visit(const SmallerOrEqualThen& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(<=, lhs, rhs);
}

void
EvalVisitor::visit(const LargerOrEqualThen& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(>=, lhs, rhs);
}

void
EvalVisitor::visit(const ShiftLeft& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(<<, lhs, rhs);
}

void
EvalVisitor::visit(const ShiftRight& node, const Expr& lhs, const Expr& rhs)
{
  EVAL_BINARY_OP(>>, lhs, rhs);
}

void
EvalVisitor::visit(const LogicalNOT& node, const Expr& rhs)
{
  EVAL_UNARY_OP(!, rhs);
}

void
EvalVisitor::visit(const BitwiseNOT& node, const Expr& rhs)
{
  EVAL_UNARY_OP(~, rhs);
}

void
EvalVisitor::visit(const Condition& node, const Expr& expr, const Expr& lhs, const Expr& rhs)
{
  expr.accept(*this);
  assert(!m_stack.empty());
  Value expr_value = m_stack.back();
  m_stack.pop_back();

  if (expr_value.get_integer())
  {
    lhs.accept(*this);
  }
  else
  {
    rhs.accept(*this);
  }
}

void
EvalVisitor::visit(const Negate& node, const Expr& expr)
{
  EVAL_UNARY_OP(!, expr);
}

void
EvalVisitor::visit(const Function& node)
{
  ScriptFunction func = m_env.lookup_function(node.get_name());

  std::vector<Value> args;

  for(const auto& it : node.get_args())
  {
    it->accept(*this);
    assert(!m_stack.empty());
    args.push_back(m_stack.back());
    m_stack.pop_back();
  }

  m_stack.push_back(func(args));
}

void
EvalVisitor::visit(const Variable& node)
{
  m_stack.push_back(m_env.lookup_variable(node.get_name()));
}

void
EvalVisitor::visit(const Integer& node)
{
  m_stack.push_back(Value::integer(node.get_value()));
}

void
EvalVisitor::visit(const Real& node)
{
  m_stack.push_back(Value::real(node.get_value()));
}

/* EOF */
