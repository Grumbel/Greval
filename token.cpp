#include <assert.h>
#include <ostream>

#include "token.hpp"

std::ostream& operator<<(std::ostream& os, const Token& token)
{
  token.print(os);
  return os;
}

void
Token::print(std::ostream& os) const
{
  switch(m_type)
  {
    case kInteger: os << "integer:" << m_value.integer; break;
    case kReal:    os << "real:" << m_value.real; break;
    case kPlus:    os << "+"; break;
    case kMinus:   os << "*"; break;
    case kMult:    os << "/"; break;
    case kDiv:     os << "/"; break;
    case kEOF:     os << "EOF"; break;
    default:       assert(!"never reached");
  }
}

/* EOF */
