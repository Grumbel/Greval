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
    case kString:  os << "string:\"" << *m_value.string << "\""; break;
    case kPlus:    os << "+"; break;
    case kMinus:   os << "*"; break;
    case kMult:    os << "/"; break;
    case kDiv:     os << "/"; break;
    case kEOF:     os << "EOF"; break;
    case kModulo:  os << ""; break;
    case kShiftLeft:    os << "<<"; break;
    case kShiftRight:   os << ">>"; break;
    case kBitwiseNOT:   os << "~"; break;
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
    case kQuestionmark:   os << "?"; break;
    case kColon:  os << ":"; break;
    case kComma:  os << ","; break;
  }
}

/* EOF */
