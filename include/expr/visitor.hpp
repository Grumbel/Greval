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

  virtual void visit(const Plus& node) = 0;
  virtual void visit(const Minus& node) = 0;
  virtual void visit(const Mult& node) = 0;
  virtual void visit(const Div& node) = 0;
  virtual void visit(const Modulo& node) = 0;
  virtual void visit(const LogicalAND& node) = 0;
  virtual void visit(const LogicalOR& node) = 0;
  virtual void visit(const BitwiseAND& node) = 0;
  virtual void visit(const BitwiseXOR& node) = 0;
  virtual void visit(const BitwiseOR& node) = 0;
  virtual void visit(const Equal& node) = 0;
  virtual void visit(const NotEqual& node) = 0;
  virtual void visit(const LargerThen& node) = 0;
  virtual void visit(const SmallerThen& node) = 0;
  virtual void visit(const SmallerOrEqualThen& node) = 0;
  virtual void visit(const LargerOrEqualThen& node) = 0;
  virtual void visit(const ShiftLeft& node) = 0;
  virtual void visit(const ShiftRight& node) = 0;
  virtual void visit(const LogicalNOT& node) = 0;
  virtual void visit(const BitwiseNOT& node) = 0;
  virtual void visit(const Condition& node) = 0;
  virtual void visit(const Negate& node) = 0;
  virtual void visit(const Function& node) = 0;
  virtual void visit(const Variable& node) = 0;
  virtual void visit(const Integer& node) = 0;
  virtual void visit(const Real& node) = 0;
};

} // namespace expr

#endif

/* EOF */
