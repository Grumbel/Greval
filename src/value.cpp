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

#include <math.h>
#include <ostream>
#include <stdexcept>

#include "value.hpp"

void
Value::print(std::ostream& os) const
{
  os.setf(std::ios_base::fixed, std::ios_base::floatfield);

  switch(m_type)
  {
    case Value::kReal:    os << "real:" << m_value.real; break;
    case Value::kInteger: os << "integer:" << m_value.integer; break;
    case Value::kString:  os << "string:\"" << *m_value.string << '"'; break;
  }
}

std::ostream& operator<<(std::ostream& os, const Value& value)
{
  value.print(os);
  return os;
}

Value
Value::operator+(const Value& rhs) const
{
  if (this->get_type() == kInteger && rhs.get_type() == kInteger)
  {
    return Value::integer(m_value.integer + rhs.m_value.integer);
  }
  else
  {
    return Value::real(this->get_real() + rhs.get_real());
  }
}

Value
Value::operator-(const Value& rhs) const
{
  if (this->get_type() == kInteger && rhs.get_type() == kInteger)
  {
    return Value::integer(m_value.integer - rhs.m_value.integer);
  }
  else
  {
    return Value::real(this->get_real() - rhs.get_real());
  }
}

Value
Value::operator*(const Value& rhs) const
{
  if (this->get_type() == kInteger && rhs.get_type() == kInteger)
  {
    return Value::integer(m_value.integer * rhs.m_value.integer);
  }
  else
  {
    return Value::real(this->get_real() * rhs.get_real());
  }
}

Value
Value::operator/(const Value& rhs) const
{
  if (this->get_type() == kInteger && rhs.get_type() == kInteger)
  {
    return Value::integer(m_value.integer / rhs.m_value.integer);
  }
  else
  {
    return Value::real(this->get_real() / rhs.get_real());
  }
}

Value
Value::operator%(const Value& rhs) const
{
  if (this->get_type() == kInteger && rhs.get_type() == kInteger)
  {
    return Value::integer(m_value.integer % rhs.m_value.integer);
  }
  else
  {
    return Value::real(fmodf(this->get_real(), rhs.get_real()));
  }
}

Value
Value::operator<<(const Value& rhs) const
{
  if (this->get_type() == kInteger && rhs.get_type() == kInteger)
  {
    return Value::integer(m_value.integer << rhs.m_value.integer);
  }
  else
  {
    throw std::runtime_error("illegal operation << on Real");
  }
}

Value
Value::operator>>(const Value& rhs) const
{
  if (this->get_type() == kInteger && rhs.get_type() == kInteger)
  {
    return Value::integer(m_value.integer >> rhs.m_value.integer);
  }
  else
  {
    throw std::runtime_error("illegal operation >> on Real");
  }
}

Value
Value::operator<(const Value& rhs) const
{
  return Value::integer(this->get_real() < rhs.get_real());
}

Value
Value::operator>(const Value& rhs) const
{
  return Value::integer(this->get_real() > rhs.get_real());
}

Value
Value::operator<=(const Value& rhs) const
{
  return Value::integer(this->get_real() <= rhs.get_real());
}

Value
Value::operator>=(const Value& rhs) const
{
  return Value::integer(this->get_real() >= rhs.get_real());
}

Value
Value::operator==(const Value& rhs) const
{
  return Value::integer(this->get_real() == rhs.get_real());
}

Value
Value::operator!=(const Value& rhs) const
{
  return Value::integer(this->get_real() != rhs.get_real());
}

Value
Value::logical_and(const Value& rhs) const
{
  return Value::integer(get_integer() && rhs.get_integer());
}

Value
Value::logical_or(const Value& rhs) const
{
  return Value::integer(get_integer() || rhs.get_integer());
}

Value
Value::operator&(const Value& rhs) const
{
  if (this->get_type() == kInteger && rhs.get_type() == kInteger)
  {
    return Value::integer(m_value.integer & rhs.m_value.integer);
  }
  else
  {
    throw std::runtime_error("illegal operation & on Real");
  }
}

Value
Value::operator^(const Value& rhs) const
{
  if (this->get_type() == kInteger && rhs.get_type() == kInteger)
  {
    return Value::integer(m_value.integer ^ rhs.m_value.integer);
  }
  else
  {
    throw std::runtime_error("illegal operation ^ on Real");
  }
}

Value
Value::operator|(const Value& rhs) const
{
  if (this->get_type() == kInteger && rhs.get_type() == kInteger)
  {
    return Value::integer(m_value.integer | rhs.m_value.integer);
  }
  else
  {
    throw std::runtime_error("illegal operation | on Real");
  }
}

Value
Value::operator~() const
{
  switch(this->get_type())
  {
    case kInteger:
      return Value::integer(~m_value.integer);

    case kReal:
      throw std::runtime_error("illegal operation ~ on Real");

    case kString:
      throw std::runtime_error("illegal operation ~ on String");
  }

  return Value();
}

Value
Value::operator!() const
{
  switch(this->get_type())
  {
    case kInteger:
      return Value::integer(!m_value.integer);

    case kReal:
      return Value::integer(!m_value.real);

    case kString:
      throw std::runtime_error("illegal operation ! on String");
  }

  return Value();
}

Value::operator bool() const
{
  switch(this->get_type())
  {
    case kInteger:
      return reinterpret_cast<void*>(m_value.integer != 0);

    case kReal:
      return reinterpret_cast<void*>(m_value.real != 0);

    case kString:
      return reinterpret_cast<void*>(!m_value.string->empty());
  }

  return false;
}

Value
Value::operator-() const
{
  switch(this->get_type())
  {
    case kInteger:
      return Value::integer(-m_value.integer);

    case kReal:
      return Value::real(-m_value.real);

    case kString:
      throw std::runtime_error("illegal operation - on String");
  }

  return Value();
}

/* EOF */
