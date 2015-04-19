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

#define EVAL_BINARY_FUNC(func, lhs, rhs) \
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
  m_stack.push_back(lhs_value.func(rhs_value))

#define EVAL_UNARY_OP(op, rhs) \
  rhs.accept(*this); \
  assert(!m_stack.empty()); \
  Value rhs_value = m_stack.back(); \
  m_stack.pop_back(); \
  \
  m_stack.push_back(op rhs_value)

void
EvalVisitor::visit(const Plus& node)
{
  EVAL_BINARY_OP(+, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const Minus& node)
{
  EVAL_BINARY_OP(-, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const Mult& node)
{
  EVAL_BINARY_OP(*, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const Div& node)
{
  EVAL_BINARY_OP(/, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const Modulo& node)
{
  EVAL_BINARY_OP(%, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const LogicalAND& node)
{
  EVAL_BINARY_FUNC(logical_and, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const LogicalOR& node)
{
  EVAL_BINARY_FUNC(logical_or, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const BitwiseAND& node)
{
  EVAL_BINARY_OP(&, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const BitwiseXOR& node)
{
  EVAL_BINARY_OP(^, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const BitwiseOR& node)
{
  EVAL_BINARY_OP(|, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const Equal& node)
{
  EVAL_BINARY_OP(==, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const NotEqual& node)
{
  EVAL_BINARY_OP(!=, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const LargerThen& node)
{
  EVAL_BINARY_OP(>, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const SmallerThen& node)
{
  EVAL_BINARY_OP(<, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const SmallerOrEqualThen& node)
{
  EVAL_BINARY_OP(<=, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const LargerOrEqualThen& node)
{
  EVAL_BINARY_OP(>=, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const ShiftLeft& node)
{
  EVAL_BINARY_OP(<<, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const ShiftRight& node)
{
  EVAL_BINARY_OP(>>, node.get_lhs(), node.get_rhs());
}

void
EvalVisitor::visit(const LogicalNOT& node)
{
  EVAL_UNARY_OP(!, node.get_rhs());
}

void
EvalVisitor::visit(const BitwiseNOT& node)
{
  EVAL_UNARY_OP(~, node.get_rhs());
}

void
EvalVisitor::visit(const Condition& node)
{
  node.get_expr().accept(*this);
  assert(!m_stack.empty());
  Value expr_value = m_stack.back();
  m_stack.pop_back();

  if (expr_value.get_integer())
  {
    node.get_lhs().accept(*this);
  }
  else
  {
    node.get_rhs().accept(*this);
  }
}

void
EvalVisitor::visit(const Negate& node)
{
  EVAL_UNARY_OP(-, node.get_rhs());
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
