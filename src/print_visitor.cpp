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

#include "print_visitor.hpp"

#include <iostream>

#include "syntax_tree.hpp"

PrintVisitor::PrintVisitor(std::ostream& os) :
  m_os(os)
{
}

void
PrintVisitor::visit(const Plus& node)
{
  m_os << "(+ ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Minus& node)
{
  m_os << "(- ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Mult& node)
{
  m_os << "(* ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Div& node)
{
  m_os << "(/ ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Modulo& node)
{
  m_os << "(% ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const LogicalAND& node)
{
  m_os << "(&& ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const LogicalOR& node)
{
  m_os << "(|| ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const BitwiseAND& node)
{
  m_os << "(& ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const BitwiseXOR& node)
{
  m_os << "(^ ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const BitwiseOR& node)
{
  m_os << "(| ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Equal& node)
{
  m_os << "(== ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const NotEqual& node)
{
  m_os << "(!= ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const LargerThen& node)
{
  m_os << "(> ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const SmallerThen& node)
{
  m_os << "(< ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const SmallerOrEqualThen& node)
{
  m_os << "(<= ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const LargerOrEqualThen& node)
{
  m_os << "(>= ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const ShiftLeft& node)
{
  m_os << "(<< ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const ShiftRight& node)
{
  m_os << "(>> ";
  node.get_lhs().accept(*this);
  m_os << " ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const LogicalNOT& node)
{
  m_os << "(! ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const BitwiseNOT& node)
{
  m_os << "(~ ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Condition& node)
{
  m_os << "(? ";
  node.get_expr().accept(*this);
  m_os << " : ";
  node.get_lhs().accept(*this);
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Negate& node)
{
  m_os << "(- ";
  node.get_rhs().accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Function& node)
{
  m_os << "(" << node.get_name();
  for(const auto& arg : node.get_args())
  {
    m_os << " ";
    arg->accept(*this);
  }
  m_os << ")";
}

void
PrintVisitor::visit(const Variable& node)
{
  m_os << node.get_name();
}

void
PrintVisitor::visit(const Integer& node)
{
  m_os << node.get_value();
}

void
PrintVisitor::visit(const Real& node)
{
  m_os << node.get_value();
}

/* EOF */
