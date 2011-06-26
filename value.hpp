#ifndef HEADER_VALUE_HPP
#define HEADER_VALUE_HPP

#include <iosfwd>

class Value
{
public:
  enum Type {
    kInteger,
    kReal
  };

private:
  Type m_type;
  union {
    int   integer;
    float real;
  } m_value;

public:
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
    m_type(),
    m_value()
  {}

public:
  Type get_type() const { return m_type; }

  int get_integer() { 
    switch(m_type)
    {
      case kReal:    return static_cast<int>(m_value.real); 
      case kInteger: return m_value.integer; 
    }
  }

  float get_real() const {
    switch(m_type)
    {
      case kReal:    return m_value.real; 
      case kInteger: return static_cast<float>(m_value.integer); 
    }
  }

  void print(std::ostream& os) const;

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

  Value operator~() const;
  Value operator!() const;
};

std::ostream& operator<<(std::ostream& os, const Value& value);

#endif

/* EOF */
