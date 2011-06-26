#include <assert.h>
#include <stdlib.h>
#include <iostream>
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
      str += c;
      while((c = get_char()) != -1)
      {
        if (c == '.' && !real)
        {
          real = true;
          str += c;
        }
        else if (!isdigit(c))
        {
          unget_char();
          break;
        }
        else
        {
          str += c;
        }
      }

      if (real)
      {
        return Token::real(atof(str.c_str()));
      }
      else
      {
        return Token::integer(atoi(str.c_str()));
      }
    }
    else if (isalpha(c)) // 
    {
      while((c = get_char()) != -1)
      {
      }
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
