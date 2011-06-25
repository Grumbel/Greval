#ifndef HEADER_TOKEN_HPP
#define HEADER_TOKEN_HPP

#include <iosfwd>

class Token
{
public:
  enum Type {
    kInteger,
    kReal,
    kPlus,
    kMinus,
    kMult,
    kDiv,
    kParentLeft,
    kParentRight,
    kEOF
  };

public:
  Token() :
    m_type(kEOF),
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

  Token(Type type) :
    m_type(type),
    m_value()
  {}
  
  Type  get_type() const { return m_type; }
  int   get_integer() const { return m_value.integer; }
  float get_real() const { return m_value.real; }

  void print(std::ostream& os) const;

private:
  Type m_type;
  union {
    int   integer;
    float real;
  } m_value;

public:
  static Token minus() { return Token(kMinus); }
  static Token plus()  { return Token(kPlus);  }
  static Token mult()  { return Token(kMult);  }
  static Token div()   { return Token(kDiv);   }
  static Token parent_left()   { return Token(kParentLeft);   }
  static Token parent_right()   { return Token(kParentRight); }

  static Token integer(int num) { return Token(kInteger, num); }
  static Token real(float num)  { return Token(kReal,    num); }

  static Token eof()            { return Token(kEOF); }
};

std::ostream& operator<<(std::ostream& os, const Token& token);

#endif

/* EOF */
