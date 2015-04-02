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
