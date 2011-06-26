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
    case kModulo:  os << ""; break;
    case kShiftLeft:    os << "<<"; break;
    case kShiftRight:   os << ">>"; break;
    case kBitwiseXOR:   os << "^"; break;
    case kBitwiseOR:    os << "|"; break;
    case kBitwiseAND:   os << "&"; break;
    case kLogicalOR:    os << "||"; break;
    case kLogicalAND:   os << "&&"; break;
    case kLogicalNOT:   os << "!"; break;
    case kLargerThen:   os << ">"; break;
    case kSmallerThen:  os << "<"; break;
    case kLargerOrEqualThen:  os << ">="; break;
    case kSmallerOrEqualThen: os << "<="; break;
    case kEqual:        os << "=="; break;
    case kNotEqual:     os << "!="; break;
    case kParentLeft:   os << "("; break;
    case kParentRight:  os << ")"; break;
  }
}

/* EOF */
