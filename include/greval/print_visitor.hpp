// Greval - A simple toy programming language
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

namespace greval {

class PrintVisitor : public Visitor
{
private:
  std::ostream& m_os;

public:
  PrintVisitor(std::ostream& os);

  void visit(Plus const& node) override;
  void visit(Minus const& node) override;
  void visit(Mult const& node) override;
  void visit(Div const& node) override;
  void visit(Modulo const& node) override;
  void visit(LogicalAND const& node) override;
  void visit(LogicalOR const& node) override;
  void visit(BitwiseAND const& node) override;
  void visit(BitwiseXOR const& node) override;
  void visit(BitwiseOR const& node) override;
  void visit(Equal const& node) override;
  void visit(NotEqual const& node) override;
  void visit(LargerThen const& node) override;
  void visit(SmallerThen const& node) override;
  void visit(SmallerOrEqualThen const& node) override;
  void visit(LargerOrEqualThen const& node) override;
  void visit(ShiftLeft const& node) override;
  void visit(ShiftRight const& node) override;
  void visit(LogicalNOT const& node) override;
  void visit(BitwiseNOT const& node) override;
  void visit(Condition const& node) override;
  void visit(Negate const& node) override;
  void visit(Function const& node) override;
  void visit(Variable const& node) override;
  void visit(Integer const& node) override;
  void visit(Real const& node) override;
};

} // namespace greval

#endif

/* EOF */
