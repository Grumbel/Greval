#include "print_visitor.hpp"

#include <iostream>

#include "syntax_tree.hpp"

PrintVisitor::PrintVisitor()
{
}

void
PrintVisitor::visit(const Plus& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(+ ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const Minus& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(- ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const Mult& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(* ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const Div& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(/ ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const Modulo& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(% ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const BitwiseAND& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(& ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const BitwiseXOR& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(^ ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const BitwiseOR& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(| ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const Equal& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(== ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const NotEqual& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(!= ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const LargerThen& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(> ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const SmallerThen& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(< ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const SmallerOrEqualThen& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(<= ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const LargerOrEqualThen& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(>= ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const ShiftLeft& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(<< ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const ShiftRight& node, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(>> ";
  lhs.accept(*this);
  std::cout << " ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const LogicalNOT& node, const Expr& rhs)
{
  std::cout << "(! ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const BitwiseNOT& node, const Expr& rhs)
{
  std::cout << "(~ ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const Condition& node, const Expr& expr, const Expr& lhs, const Expr& rhs)
{
  std::cout << "(? ";
  expr.accept(*this);
  std::cout << " : ";
  lhs.accept(*this);
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const Negate& node, const Expr& rhs)
{
 std::cout << "(! ";
  rhs.accept(*this);
  std::cout << ")";
}

void
PrintVisitor::visit(const Function& node)
{
  std::cout << "(" << node.get_name();
  //rhs.accept(*this);
  std::cout << " ...)";
}

void
PrintVisitor::visit(const Variable& node)
{
  std::cout << node.get_name();
}

void
PrintVisitor::visit(const Integer& node)
{
  std::cout << node.get_value();
}

void
PrintVisitor::visit(const Real& node)
{
  std::cout << node.get_value();
}

/* EOF */
