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

#ifndef HEADER_PARSER_HPP
#define HEADER_PARSER_HPP

#include <deque>

#include "lexer.hpp"

class Expr;

class Parser
{
private:
  Lexer& m_lexer;
  std::deque<Token> m_tokens;

public:
  Parser(Lexer& lexer);
  Expr* parse();

private:
  Expr* expr();
  Expr* conditional_expr();
  Expr* logical_or();
  Expr* logical_and();
  Expr* bitwise_or();
  Expr* bitwise_xor();
  Expr* bitwise_and();
  Expr* equality_expr();
  Expr* relational_expr();
  Expr* shift_expr();
  Expr* additive_expr();
  Expr* multiplicative_expr();
  Expr* unary_expr();
  Expr* primary_expression();
  void match(Token::Type token_type);

  void error(const std::string& msg);

  Token::Type get_token_type(int lookahead = 0);
  Token get_token(int lookahead = 0);
  void  next_token();

private:
  Parser(const Parser&);
  Parser& operator=(const Parser&);
};

#endif

/* EOF */
