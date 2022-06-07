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

#ifndef HEADER_TOKEN_HPP
#define HEADER_TOKEN_HPP

#include <iosfwd>

class Token
{
public:
  enum class Type {
    kInteger,
    kReal,
    kString,
    kPlus,
    kMinus,
    kMult,
    kDiv,
    kComma,
    kModulo,
    kShiftLeft,
    kShiftRight,
    kBitwiseNOT,
    kBitwiseXOR,
    kBitwiseOR,
    kBitwiseAND,
    kLogicalNOT,
    kLogicalOR,
    kLogicalAND,
    kLargerThen,
    kSmallerThen,
    kQuestionmark,
    kColon,
    kLargerOrEqualThen,
    kSmallerOrEqualThen,
    kEqual,
    kNotEqual,
    kParentLeft,
    kParentRight,
    kEOF
  };

public:
  Token() :
    m_type(Token::Type::kEOF),
    m_value()
  {}

  Token(Type type, float num) :
    m_type(type),
    m_value()
  {
    m_value.real = num;
  }

  Token(Type type, int num) :
    m_type(type),
    m_value()
  {
    m_value.integer = num;
  }

  Token(Type type, const std::string& str) :
    m_type(type),
    m_value()
  {
    m_value.string = new std::string(str);
  }

  Token(Type type) :
    m_type(type),
    m_value()
  {}

  Token(const Token& rhs) :
    m_type(rhs.m_type),
    m_value(rhs.m_value)
  {
    if (rhs.m_type == Token::Type::kString)
    {
      m_value.string = new std::string(*rhs.m_value.string);
    }
  }

  ~Token()
  {
    if (m_type == Token::Type::kString)
    {
      delete m_value.string;
    }
  }

  Token& operator=(const Token& rhs)
  {
    if (this != &rhs)
    {
      m_type = rhs.m_type;

      if (rhs.m_type == Token::Type::kString)
      {
        m_value.string = new std::string(*rhs.m_value.string);
      }
      else
      {
        m_value = rhs.m_value;
      }
    }
    return *this;
  }

  Type  get_type() const { return m_type; }
  int   get_integer() const { return m_value.integer; }
  float get_real() const { return m_value.real; }
  std::string get_string() const { return *m_value.string; }

  void print(std::ostream& os) const;

private:
  Type m_type;
  union {
    int   integer;
    float real;
    std::string* string;
  } m_value;

public:
  static Token minus() { return Token(Token::Type::kMinus); }
  static Token plus()  { return Token(Token::Type::kPlus);  }
  static Token mult()  { return Token(Token::Type::kMult);  }
  static Token div()   { return Token(Token::Type::kDiv);   }
  static Token modulo()   { return Token(Token::Type::kModulo);   }
  static Token shift_left()   { return Token(Token::Type::kShiftLeft);   }
  static Token shift_right()  { return Token(Token::Type::kShiftRight);  }
  static Token parent_left()  { return Token(Token::Type::kParentLeft);  }
  static Token parent_right() { return Token(Token::Type::kParentRight); }

  static Token bitwise_not() { return Token(Token::Type::kBitwiseNOT); }
  static Token bitwise_or() { return Token(Token::Type::kBitwiseOR); }
  static Token bitwise_xor() { return Token(Token::Type::kBitwiseXOR); }
  static Token bitwise_and() { return Token(Token::Type::kBitwiseAND); }

  static Token logical_not() { return Token(Token::Type::kLogicalNOT); }
  static Token logical_and() { return Token(Token::Type::kLogicalAND); }
  static Token logical_or() { return Token(Token::Type::kLogicalOR); }

  static Token larger_then() { return Token(Token::Type::kLargerThen); }
  static Token larger_or_equal_then() { return Token(Token::Type::kLargerOrEqualThen); }

  static Token smaller_then() { return Token(Token::Type::kSmallerThen); }
  static Token smaller_or_equal_then() { return Token(Token::Type::kSmallerOrEqualThen); }

  static Token equal() { return Token(Token::Type::kEqual); }
  static Token not_equal() { return Token(Token::Type::kNotEqual); }

  static Token questionmark() { return Token(Token::Type::kQuestionmark); }
  static Token colon() { return Token(Token::Type::kColon); }
  static Token comma() { return Token(Token::Type::kComma); }

  static Token integer(int num) { return Token(Token::Type::kInteger, num); }
  static Token real(float num)  { return Token(Token::Type::kReal,    num); }
  static Token string(const std::string& str)  { return Token(Token::Type::kString, str); }

  static Token eof()            { return Token(Token::Type::kEOF); }
};

std::ostream& operator<<(std::ostream& os, const Token& token);

#endif

/* EOF */
