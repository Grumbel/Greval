//  Expr - A simple toy programming language
//  Copyright (C) 2011 Ingo Ruhnke <grumbel@gmail.com>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <stdexcept>
#include <sstream>
#include <vector>

#include "lexer.hpp"
#include "syntax_tree.hpp"

#include "parser.hpp"

Parser::Parser(Lexer& lexer) :
  m_lexer(lexer),
  m_tokens()
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
  return conditional_expr();
}

Expr*
Parser::conditional_expr()
{
  Expr* expr = bitwise_xor();
  while(true)
  {
    switch(get_token_type())
    {
      case Token::kQuestionmark:
        {
          next_token();
          Expr* lhs = this->expr();
          match(Token::kColon);
          Expr* rhs = bitwise_xor();
          expr = new Condition(expr, lhs, rhs);
        }
        break;
                
      default:
        return expr;
    }
  }
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
  Expr* lhs = bitwise_xor();
  while(true)
  {
    switch(get_token_type())
    {
      case Token::kBitwiseOR:
        next_token();
        lhs = new BitwiseOR(lhs, bitwise_xor());
        break;
                
      default:
        return lhs;
    }
  }
}

Expr*
Parser::bitwise_xor()
{
  Expr* lhs = bitwise_and();
  while(true)
  {
    switch(get_token_type())
    {
      case Token::kBitwiseXOR:
        next_token();
        lhs = new BitwiseXOR(lhs, bitwise_and());
        break;
                
      default:
        return lhs;
    }
  }
}

Expr*
Parser::bitwise_and()
{
  Expr* lhs = equality_expr();
  while(true)
  {
    switch(get_token_type())
    {
      case Token::kBitwiseAND:
        next_token();
        lhs = new BitwiseAND(lhs, equality_expr());
        break;
                
      default:
        return lhs;
    }
  }
}

Expr*
Parser::equality_expr()
{
  Expr* lhs = relational_expr();
  while(true)
  {
    switch(get_token_type())
    {
      case Token::kEqual:
        next_token();
        lhs = new Equal(lhs, relational_expr());
        break;

      case Token::kNotEqual:
        next_token();
        lhs = new NotEqual(lhs, relational_expr());
        break;
                
      default:
        return lhs;
    }
  }
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

    case Token::kMinus:
      next_token();
      return new Negate(unary_expr());

    case Token::kPlus:
      next_token();
      return unary_expr();

    default:
      return primary_expression();
  }
}

Expr*
Parser::primary_expression()
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

    case Token::kString:
      {
        std::string name = get_token().get_string();
        next_token();
        if (get_token_type() == Token::kParentLeft)
        {
          match(Token::kParentLeft);
          std::vector<Expr*> args;
          if (get_token_type() != Token::kParentRight)
          {
            while(1)
            {
              args.push_back(expr());
              if (get_token_type() == Token::kComma)
              {
                match(Token::kComma);
              }
              else
              {
                break;
              }
            }
          }
          match(Token::kParentRight); 
          lhs = new Function(name, args);
        }
        else
        {
          lhs = new Variable(name);
        }
      }
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
    std::ostringstream out;
    out << "syntax error: expected: " << token_type << " got " << get_token_type();
    error(out.str());
  }
}

void
Parser::error(const std::string& msg)
{
  throw std::runtime_error(msg);
}

Token::Type
Parser::get_token_type(int lookahead)
{
  return get_token(lookahead).get_type();
}

Token
Parser::get_token(int lookahead)
{
  while (lookahead >= static_cast<int>(m_tokens.size()))
  {
    m_tokens.push_back(m_lexer.get_token());
  }
  return m_tokens[lookahead];
}

void
Parser::next_token()
{
  if (!m_tokens.empty())
  {
    m_tokens.pop_front();
  }

  if (m_tokens.empty())
  {
    m_tokens.push_back(m_lexer.get_token());
  }
}

/* EOF */
