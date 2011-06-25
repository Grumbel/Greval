#ifndef HEADER_LEXER_HPP
#define HEADER_LEXER_HPP

#include <string>

#include "token.hpp"

class Lexer
{
private:
  const std::string m_string;
  std::string::size_type m_pos;

public:
  Lexer(const std::string& str);
  
  Token get_token();
  bool is_eof() const;

private:
  int  get_char();
  void unget_char();

  const char* get_ptr();

private:
  Lexer(const Lexer&);
  Lexer& operator=(const Lexer&);
};

#endif

/* EOF */
