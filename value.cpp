#include <math.h>
#include <ostream>

#include "value.hpp"

void
Value::print(std::ostream& os) const
{
  switch(m_type)
  {
    case Value::kReal:    os << "real:" << m_value.real; break;
    case Value::kInteger: os << "integer:" << m_value.integer; break;
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

/* EOF */
