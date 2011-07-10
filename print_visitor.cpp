#include "print_visitor.hpp"

#include <iostream>

#include "syntax_tree.hpp"

PrintVisitor::PrintVisitor(std::ostream& os) :
  m_os(os)
{
}

void
PrintVisitor::visit(const Plus& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(+ ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Minus& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(- ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Mult& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(* ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Div& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(/ ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Modulo& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(% ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const BitwiseAND& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(& ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const BitwiseXOR& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(^ ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const BitwiseOR& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(| ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Equal& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(== ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const NotEqual& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(!= ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const LargerThen& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(> ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const SmallerThen& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(< ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const SmallerOrEqualThen& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(<= ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const LargerOrEqualThen& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(>= ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const ShiftLeft& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(<< ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const ShiftRight& node, const Expr& lhs, const Expr& rhs)
{
  m_os << "(>> ";
  lhs.accept(*this);
  m_os << " ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const LogicalNOT& node, const Expr& rhs)
{
  m_os << "(! ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const BitwiseNOT& node, const Expr& rhs)
{
  m_os << "(~ ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Condition& node, const Expr& expr, const Expr& lhs, const Expr& rhs)
{
  m_os << "(? ";
  expr.accept(*this);
  m_os << " : ";
  lhs.accept(*this);
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Negate& node, const Expr& rhs)
{
 m_os << "(! ";
  rhs.accept(*this);
  m_os << ")";
}

void
PrintVisitor::visit(const Function& node)
{
  m_os << "(" << node.get_name();
  //rhs.accept(*this);
  m_os << " ...)";
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
