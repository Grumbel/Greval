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

#ifndef HEADER_EVAL_VISITOR_HPP
#define HEADER_EVAL_VISITOR_HPP

#include <vector>

#include "value.hpp"
#include "visitor.hpp"

namespace expr {

class Environment;

class EvalVisitor : public Visitor
{
private:
  std::vector<Value> m_stack;
  const Environment& m_env;

public:
  EvalVisitor(const Environment& env);

  Value get_result() const;

  void visit(const Plus& node) override;
  void visit(const Minus& node) override;
  void visit(const Mult& node) override;
  void visit(const Div& node) override;
  void visit(const Modulo& node) override;
  void visit(const LogicalAND& node) override;
  void visit(const LogicalOR& node) override;
  void visit(const BitwiseAND& node) override;
  void visit(const BitwiseXOR& node) override;
  void visit(const BitwiseOR& node) override;
  void visit(const Equal& node) override;
  void visit(const NotEqual& node) override;
  void visit(const LargerThen& node) override;
  void visit(const SmallerThen& node) override;
  void visit(const SmallerOrEqualThen& node) override;
  void visit(const LargerOrEqualThen& node) override;
  void visit(const ShiftLeft& node) override;
  void visit(const ShiftRight& node) override;
  void visit(const LogicalNOT& node) override;
  void visit(const BitwiseNOT& node) override;
  void visit(const Condition& node) override;
  void visit(const Negate& node) override;
  void visit(const Function& node) override;
  void visit(const Variable& node) override;
  void visit(const Integer& node) override;
  void visit(const Real& node) override;
};

} // namespace expr

#endif

/* EOF */
