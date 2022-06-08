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

#include "print_visitor.hpp"

#include <iostream>

#include "syntax_tree.hpp"

namespace greval {

PrintVisitor::PrintVisitor(std::ostream& os) :
  m_os(os)
{
}

void
PrintVisitor::visit(Plus const& node)
{
  m_os << "(+ ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(Minus const& node)
{
  m_os << "(- ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(Mult const& node)
{
  m_os << "(* ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(Div const& node)
{
  m_os << "(/ ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(Modulo const& node)
{
  m_os << "(% ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(LogicalAND const& node)
{
  m_os << "(&& ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(LogicalOR const& node)
{
  m_os << "(|| ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(BitwiseAND const& node)
{
  m_os << "(& ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(BitwiseXOR const& node)
{
  m_os << "(^ ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(BitwiseOR const& node)
{
  m_os << "(| ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(Equal const& node)
{
  m_os << "(== ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(NotEqual const& node)
{
  m_os << "(!= ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(LargerThen const& node)
{
  m_os << "(> ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(SmallerThen const& node)
{
  m_os << "(< ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(SmallerOrEqualThen const& node)
{
  m_os << "(<= ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(LargerOrEqualThen const& node)
{
  m_os << "(>= ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(ShiftLeft const& node)
{
  m_os << "(<< ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(ShiftRight const& node)
{
  m_os << "(>> ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(LogicalNOT const& node)
{
  m_os << "(! ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(BitwiseNOT const& node)
{
  m_os << "(~ ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(Condition const& node)
{
  m_os << "(? ";
  node.get_expr().accept(*this);
  m_os << " : ";
  node.get_lhs().accept(*this);
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(Negate const& node)
{
  m_os << "(- ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(Function const& node)
{
  m_os << "(" << node.get_name();
  for(auto const& arg : node.get_args())
  {
    m_os << " ";
    arg->accept(*this);
  }
  m_os << ")";
}

void
PrintVisitor::visit(Variable const& node)
{
  m_os << node.get_name();
}

void
PrintVisitor::visit(Integer const& node)
{
  m_os << node.get_value();
}

void
PrintVisitor::visit(Real const& node)
{
  m_os << node.get_value();
}

} // namespace greval

/* EOF */
