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

#ifndef HEADER_VISITOR_HPP
#define HEADER_VISITOR_HPP

namespace expr {

class Expr;
class Plus;
class Minus;
class Mult;
class Div;
class Modulo;
class LogicalAND;
class LogicalOR;
class BitwiseAND;
class BitwiseXOR;
class BitwiseOR;
class Equal;
class NotEqual;
class LargerThen;
class SmallerThen;
class SmallerOrEqualThen;
class LargerOrEqualThen;
class ShiftLeft;
class ShiftRight;
class LogicalNOT;
class BitwiseNOT;
class Condition;
class Negate;
class Function;
class Variable;
class Integer;
class Real;

class Visitor
{
public:
  virtual ~Visitor() {}

  virtual void visit(Plus const& node) = 0;
  virtual void visit(Minus const& node) = 0;
  virtual void visit(Mult const& node) = 0;
  virtual void visit(Div const& node) = 0;
  virtual void visit(Modulo const& node) = 0;
  virtual void visit(LogicalAND const& node) = 0;
  virtual void visit(LogicalOR const& node) = 0;
  virtual void visit(BitwiseAND const& node) = 0;
  virtual void visit(BitwiseXOR const& node) = 0;
  virtual void visit(BitwiseOR const& node) = 0;
  virtual void visit(Equal const& node) = 0;
  virtual void visit(NotEqual const& node) = 0;
  virtual void visit(LargerThen const& node) = 0;
  virtual void visit(SmallerThen const& node) = 0;
  virtual void visit(SmallerOrEqualThen const& node) = 0;
  virtual void visit(LargerOrEqualThen const& node) = 0;
  virtual void visit(ShiftLeft const& node) = 0;
  virtual void visit(ShiftRight const& node) = 0;
  virtual void visit(LogicalNOT const& node) = 0;
  virtual void visit(BitwiseNOT const& node) = 0;
  virtual void visit(Condition const& node) = 0;
  virtual void visit(Negate const& node) = 0;
  virtual void visit(Function const& node) = 0;
  virtual void visit(Variable const& node) = 0;
  virtual void visit(Integer const& node) = 0;
  virtual void visit(Real const& node) = 0;
};

} // namespace expr

#endif

/* EOF */
