#include <math.h>
#include <ostream>
#include <stdexcept>

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
/*
Value
Value::operator&&(const Value& rhs) const
{
}

Value
Value::operator||(const Value& rhs) const
{
}
*/
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
  }
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
  }
}

Value::operator void*() const
{
  switch(this->get_type())
  {
    case kInteger:
      return reinterpret_cast<void*>(m_value.integer != 0);
      
    case kReal:
      return reinterpret_cast<void*>(m_value.real != 0);
  }
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
  }
}

/* EOF */
