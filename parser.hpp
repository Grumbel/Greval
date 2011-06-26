#ifndef HEADER_PARSER_HPP
#define HEADER_PARSER_HPP

#include "lexer.hpp"

class Expr;

class Parser
{
private:
  Lexer& m_lexer;
  Token  m_current_token;

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
  Expr* factor();
  void match(Token::Type token_type);

  void error(const std::string& msg);

  Token::Type get_token_type();
  Token get_token();
  void  next_token();

private:
  Parser(const Parser&);
  Parser& operator=(const Parser&);
};

#endif

/* EOF */
