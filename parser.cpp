#include <stdexcept>

#include "lexer.hpp"
#include "syntax_tree.hpp"

#include "parser.hpp"

Parser::Parser(Lexer& lexer) :
  m_lexer(lexer),
  m_current_token()
{  
}

Expr*
Parser::parse()
{
  next_token();
  return expr();
}

Expr*
Parser::expr()
{
  return relational_expr();
}

Expr*
Parser::logical_or()
{
  return 0;
}

Expr*
Parser::logical_and()
{
  return 0;
}

Expr* 
Parser::bitwise_or()
{
  return 0;
}

Expr*
Parser::bitwise_xor()
{
  return 0;
}

Expr*
Parser::bitwise_and()
{
  return 0;
}

Expr*
Parser::equality_expr()
{
  return 0;
}

Expr*
Parser::relational_expr()
{
  Expr* lhs = shift_expr();
  while(true)
  {
    switch(get_token_type())
    {
      case Token::kLargerThen:
        next_token();
        lhs = new LargerThen(lhs, shift_expr());
        break;

      case Token::kSmallerThen:
        next_token();
        lhs = new SmallerThen(lhs, shift_expr());
        break;

      case Token::kLargerOrEqualThen:
        next_token();
        lhs = new LargerOrEqualThen(lhs, shift_expr());
        break;

      case Token::kSmallerOrEqualThen:
        next_token();
        lhs = new SmallerOrEqualThen(lhs, shift_expr());
        break;

      default:
        return lhs;
    }
  }
  return lhs;
}

Expr*
Parser::shift_expr()
{
  Expr* lhs = additive_expr();
  while(true)
  {
    switch(get_token_type())
    {
      case Token::kShiftLeft:
        next_token();
        lhs = new ShiftLeft(lhs, additive_expr());
        break;

      case Token::kShiftRight:
        next_token();
        lhs = new ShiftRight(lhs, additive_expr());
        break;

      default:
        return lhs;
    }
  }
  return lhs;
}

Expr*
Parser::additive_expr()
{
  Expr* lhs = multiplicative_expr();
  while(true)
  {
    switch(get_token_type())
    {
      case Token::kPlus:
        next_token();
        lhs = new Plus(lhs, multiplicative_expr());
        break;

      case Token::kMinus:
        next_token();
        lhs = new Minus(lhs, multiplicative_expr());
        break;

      default:
        return lhs;
    }
  }
  return lhs;
}

Expr*
Parser::multiplicative_expr()
{
  Expr* lhs = unary_expr();
  while(true)
  {
    switch(get_token_type())
    {
      case Token::kMult: 
        next_token();
        lhs = new Mult(lhs, unary_expr());
        break;

      case Token::kDiv: 
        next_token();
        lhs = new Div(lhs, unary_expr());
        break;
        
      case Token::kModulo: 
        next_token();
        lhs = new Modulo(lhs, unary_expr());
        break;

      default:
        return lhs;
    }
  }
  return lhs;
}

Expr* 
Parser::unary_expr()
{
  switch(get_token_type())
  {
    case Token::kLogicalNOT:
      next_token();
      return new LogicalNOT(unary_expr());

    case Token::kBitwiseNOT:
      next_token();
      return new BitwiseNOT(unary_expr());

    default:
      return factor();
  }
}

Expr*
Parser::factor()
{
  Expr* lhs = 0;

  switch(get_token_type())
  {
    case Token::kParentLeft:
      match(Token::kParentLeft);
      lhs = expr(); 
      match(Token::kParentRight); 
      break;

    case Token::kInteger:
      lhs = new Integer(get_token().get_integer());
      next_token();
      break;

    case Token::kReal:
      lhs = new Real(get_token().get_real());
      next_token();
      break;

    default:
      throw std::runtime_error("syntax error");
  }
  
  return lhs;
}

void
Parser::match(Token::Type token_type)
{
  if (get_token_type() == token_type)
  {
    next_token();
  }
  else
  {
    error("syntax error");
  }
}

void
Parser::error(const std::string& msg)
{
  throw std::runtime_error(msg);
}

Token::Type
Parser::get_token_type()
{
  return m_current_token.get_type();
}

Token
Parser::get_token()
{
  return m_current_token;
}

void
Parser::next_token()
{
  m_current_token = m_lexer.get_token();
}

/* EOF */
