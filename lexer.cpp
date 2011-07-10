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

#include <assert.h>
#include <stdlib.h>
#include <stdexcept>

#include "lexer.hpp"

Lexer::Lexer(const std::string& str) :
  m_string(str),
  m_pos(0)
{
}

int
Lexer::get_char()
{
  if (m_pos < m_string.size())
  {
    return m_string[m_pos++];
  }
  else
  {
    return -1;
  }
}

void
Lexer::unget_char()
{
  assert(m_pos != 0);
  m_pos -= 1;
}

const char*
Lexer::get_ptr()
{
  return &*m_string.begin() + m_pos;
}

Token
Lexer::get_token()
{
  int c;
  while((c = get_char()) != -1)
  {
    if (isspace(c))
    {
      // ignore
    }
    else if (isdigit(c) || c == '.') // number
    {
      bool real = false;

      if (c == '.')
      {
        real = true;
      }

      std::string str;
      str += static_cast<char>(c);
      while((c = get_char()) != -1)
      {
        if (c == '.' && !real)
        {
          real = true;
          str += static_cast<char>(c);
        }
        else if (!isdigit(c))
        {
          unget_char();
          break;
        }
        else
        {
          str += static_cast<char>(c);
        }
      }

      if (real)
      {
        return Token::real(static_cast<float>(atof(str.c_str())));
      }
      else
      {
        return Token::integer(atoi(str.c_str()));
      }
    }
    else if (isalpha(c))
    {
      std::string str;
      str += static_cast<char>(c);
      while((c = get_char()) != -1)
      {
        if (!isalpha(c) && !isdigit(c) && c != '_')
        {
          unget_char();
          break;
        }
        else
        {
          str += static_cast<char>(c);
        }
      }
      return Token::string(str);
    }
    else if (c == '=')
    {
      if ((c = get_char()) != -1 && c == '=')
      {
        return Token::equal();
      }
      else
      {
        throw std::runtime_error("syntax error");
      }
    }
    else if (c == '~')
    {
      return Token::bitwise_not();
    }
    else if (c == '!')
    {
      if ((c = get_char()) != -1 && c == '=')
      {
        return Token::not_equal();
      }
      else
      {
        unget_char();
        return Token::logical_not();
      }
    }
    else if (c == '<')
    {
      if ((c = get_char()) != -1)
      {
        if (c == '=')
          return Token::smaller_or_equal_then();
        else if (c == '<')
          return Token::shift_left();
        else
        {
          unget_char();
          return Token::smaller_then();
        }
      }
      else
      {
        unget_char();
        return Token::smaller_then();
      }
    }
    else if (c == '>')
    {
      if ((c = get_char()) != -1)
      {
        if (c == '=')
        {
          return Token::larger_or_equal_then();
        }
        else if (c == '>')
        {
          return Token::shift_right();
        }
        else
        {
          unget_char();
          return Token::larger_then();
        }
      }
      else
      {
        unget_char();
        return Token::larger_then();
      }
    }
    else if (c == '|')
    {
      if ((c = get_char()) != -1 && c == '|')
      {
        return Token::logical_or();
      }
      else
      {
        unget_char();
        return Token::bitwise_or();
      }
    }
    else if (c == '^')
    {
      return Token::bitwise_xor();
    }
    else if (c == '&')
    {
      if ((c = get_char()) != -1 && c == '&')
      {
        return Token::logical_and();
      }
      else
      {
        unget_char();
        return Token::bitwise_and();
      }
    }
    else if (c == '+')
    {
      return Token::plus();
    }
    else if (c == '%')
    {
      return Token::modulo();
    }
    else if (c == '-')
    {
      return Token::minus();
    }
    else if (c == '*')
    {
      return Token::mult();
    }
    else if (c == '/')
    {
      return Token::div();
    }
    else if (c == '(')
    {
      return Token::parent_left();
    }
    else if (c == ')')
    {
      return Token::parent_right();
    }
    else if (c == ',')
    {
      return Token::comma();
    }
    else if (c == '?')
    {
      return Token::questionmark();
    }
    else if (c == ':')
    {
      return Token::colon();
    }
    else
    {
      throw std::runtime_error("syntax error");
    }
  }

  return Token::eof();
}

bool
Lexer::is_eof() const
{
  return m_pos == m_string.size();
}

/* EOF */
