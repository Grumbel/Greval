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
  Expr* lhs = term();
  while(true)
  {
    switch(get_token_type())
    {
      case Token::kPlus:
        next_token();
        lhs = new Plus(lhs, term());
        break;

      case Token::kMinus:
        next_token();
        lhs = new Minus(lhs, term());
        break;

      default:
        return lhs;
    }
  }
  return lhs;
}

Expr*
Parser::term()
{
  Expr* lhs = factor();
  while(true)
  {
    switch(get_token_type())
    {
      case Token::kMult: 
        next_token();
        lhs = new Mult(lhs, factor());
        break;

      case Token::kDiv: 
        next_token();
        lhs = new Div(lhs, factor());
        break;

      default:
        return lhs;
    }
  }
  return lhs;
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
