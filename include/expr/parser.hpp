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

#ifndef HEADER_PARSER_HPP
#define HEADER_PARSER_HPP

#include <deque>

#include "lexer.hpp"

namespace expr {

class Expr;

class Parser
{
private:
  Lexer& m_lexer;
  std::deque<Token> m_tokens;

public:
  Parser(Lexer& lexer);
  std::unique_ptr<Expr> parse();

private:
  std::unique_ptr<Expr> expr();
  std::unique_ptr<Expr> conditional_expr();
  std::unique_ptr<Expr> logical_or();
  std::unique_ptr<Expr> logical_and();
  std::unique_ptr<Expr> bitwise_or();
  std::unique_ptr<Expr> bitwise_xor();
  std::unique_ptr<Expr> bitwise_and();
  std::unique_ptr<Expr> equality_expr();
  std::unique_ptr<Expr> relational_expr();
  std::unique_ptr<Expr> shift_expr();
  std::unique_ptr<Expr> additive_expr();
  std::unique_ptr<Expr> multiplicative_expr();
  std::unique_ptr<Expr> unary_expr();
  std::unique_ptr<Expr> primary_expression();
  void match(Token::Type token_type);

  void error(std::string const& msg);

  Token::Type get_token_type(int lookahead = 0);
  Token get_token(int lookahead = 0);
  void  next_token();

private:
  Parser(Parser const&);
  Parser& operator=(Parser const&);
};

} // namespace expr

#endif

/* EOF */
