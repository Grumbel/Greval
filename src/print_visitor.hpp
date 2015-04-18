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

#ifndef HEADER_PRINT_VISITOR_HPP
#define HEADER_PRINT_VISITOR_HPP

#include <iosfwd>

#include "visitor.hpp"

class PrintVisitor : public Visitor
{
private:
  std::ostream& m_os;

public:
  PrintVisitor(std::ostream& os);

  void visit(const Plus& node);
  void visit(const Minus& node);
  void visit(const Mult& node);
  void visit(const Div& node);
  void visit(const Modulo& node);
  void visit(const BitwiseAND& node);
  void visit(const BitwiseXOR& node);
  void visit(const BitwiseOR& node);
  void visit(const Equal& node);
  void visit(const NotEqual& node);
  void visit(const LargerThen& node);
  void visit(const SmallerThen& node);
  void visit(const SmallerOrEqualThen& node);
  void visit(const LargerOrEqualThen& node);
  void visit(const ShiftLeft& node);
  void visit(const ShiftRight& node);
  void visit(const LogicalNOT& node);
  void visit(const BitwiseNOT& node);
  void visit(const Condition& node);
  void visit(const Negate& node);
  void visit(const Function& node);
  void visit(const Variable& node);
  void visit(const Integer& node);
  void visit(const Real& node);
};

#endif

/* EOF */
