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

  int get_integer() { 
    switch(m_type)
    {
      case kReal:    return static_cast<int>(m_value.real); 
      case kInteger: return m_value.integer; 
      case kString:  throw std::runtime_error("can't convert String to Integer");
    }
  }

  float get_real() const {
    switch(m_type)
    {
      case kReal:    return m_value.real; 
      case kInteger: return static_cast<float>(m_value.integer); 
      case kString:  throw std::runtime_error("can't convert String to Real");
    }

    return 0.0f;
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

  operator void*() const;
};

std::ostream& operator<<(std::ostream& os, const Value& value);

#endif

/* EOF */
