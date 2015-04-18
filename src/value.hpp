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

#ifndef HEADER_VALUE_HPP
#define HEADER_VALUE_HPP

#include <iosfwd>
#include <stdexcept>

class Value
{
public:
  enum Type {
    kInteger,
    kReal,
    kString
  };

private:
  Type m_type;
  union {
    int   integer;
    float real;
    std::string* string;
  } m_value;

public:
  static Value string(const std::string& str) {
    Value value;
    value.m_type = kString;
    value.m_value.string = new std::string(str);
    return value;
  }

  static Value integer(int v) {
    Value value;
    value.m_type = kInteger;
    value.m_value.integer = v;
    return value;
  }

  static Value real(float v) {
    Value value;
    value.m_type = kReal;
    value.m_value.real = v;
    return value;
  };

private:
  Value() :
    m_type(kInteger),
    m_value()
  {}

public:
  Value(const Value& rhs) :
    m_type(rhs.m_type),
    m_value(rhs.m_value)
  {
    if (rhs.m_type == kString)
    {
      m_value.string = new std::string(*rhs.m_value.string);
    }
  }

  Value& operator=(const Value& rhs)
  {
    if (this != &rhs)
    {
      m_type = rhs.m_type;
      if (rhs.m_type == kString)
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

  ~Value()
  {
    if (m_type == kString)
    {
      delete m_value.string;
    }
  }

  Type get_type() const { return m_type; }

  int get_integer() const {
    switch(m_type)
    {
      case kReal:
        return static_cast<int>(m_value.real);

      case kInteger:
        return m_value.integer;

      case kString:
        throw std::runtime_error("can't convert String to Integer");

      default:
        throw std::runtime_error("can't convert unknown type to Integer");
    }
  }

  float get_real() const {
    switch(m_type)
    {
      case kReal:
        return m_value.real;

      case kInteger:
        return static_cast<float>(m_value.integer);

      case kString:
        throw std::runtime_error("can't convert String to Real");

      default:
        throw std::runtime_error("can't convert unknown type to Real");
    }
  }

  void print(std::ostream& os) const;

  Value operator-() const;

  Value operator+(const Value& rhs) const;
  Value operator-(const Value& rhs) const;

  Value operator*(const Value& rhs) const;
  Value operator/(const Value& rhs) const;
  Value operator%(const Value& rhs) const;

  Value operator<<(const Value& rhs) const;
  Value operator>>(const Value& rhs) const;

  Value operator<(const Value& rhs) const;
  Value operator>(const Value& rhs) const;

  Value operator<=(const Value& rhs) const;
  Value operator>=(const Value& rhs) const;

  Value operator==(const Value& rhs) const;
  Value operator!=(const Value& rhs) const;
  /*
  Value operator&&(const Value& rhs) const;
  Value operator||(const Value& rhs) const;
  */
  Value operator&(const Value& rhs) const;
  Value operator^(const Value& rhs) const;
  Value operator|(const Value& rhs) const;

  Value operator~() const;
  Value operator!() const;

  explicit operator bool() const;
};

std::ostream& operator<<(std::ostream& os, const Value& value);

#endif

/* EOF */
