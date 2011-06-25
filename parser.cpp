#include <stdexcept>

#include "lexer.hpp"

#include "parser.hpp"

Parser::Parser(Lexer& lexer) :
  m_lexer(lexer),
  m_current_token()
{  
}

void
Parser::parse()
{
  next_token();
  expr();
}

void
Parser::expr()
{
  term();
  while(true)
  {
    switch(get_token_type())
    {
      case Token::kPlus:
        next_token();
        term();
        break;

      case Token::kMinus:
        next_token();
        term();
        break;

      default:
        return;
    }
  }
}

void
Parser::term()
{
  factor();
  while(true)
  {
    switch(get_token_type())
    {
      case Token::kMult: 
        next_token();
        factor();
        break;

      case Token::kDiv: 
        next_token();
        factor();
        break;

      default:
        return;
    }
  }
}

void
Parser::factor()
{
  switch(get_token_type())
  {
    case Token::kParentLeft:
      match(Token::kParentLeft); expr(); match(Token::kParentRight); 
      break;

    case Token::kInteger:
      next_token();
      break;

    default:
      throw std::runtime_error("syntax error");
  }
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
