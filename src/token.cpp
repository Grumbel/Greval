// Greval - A simple toy programming language
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

namespace greval {

std::ostream& operator<<(std::ostream& os, Token const& token)
{
  token.print(os);
  return os;
}

void
Token::print(std::ostream& os) const
{
  switch(m_type)
  {
    case Token::Type::kInteger: os << "integer:" << m_value.integer; break;
    case Token::Type::kReal:    os << "real:" << m_value.real; break;
    case Token::Type::kString:  os << "string:\"" << *m_value.string << "\""; break;
    case Token::Type::kPlus:    os << "+"; break;
    case Token::Type::kMinus:   os << "*"; break;
    case Token::Type::kMult:    os << "/"; break;
    case Token::Type::kDiv:     os << "/"; break;
    case Token::Type::kEOF:     os << "EOF"; break;
    case Token::Type::kModulo:  os << ""; break;
    case Token::Type::kShiftLeft:    os << "<<"; break;
    case Token::Type::kShiftRight:   os << ">>"; break;
    case Token::Type::kBitwiseNOT:   os << "~"; break;
    case Token::Type::kBitwiseXOR:   os << "^"; break;
    case Token::Type::kBitwiseOR:    os << "|"; break;
    case Token::Type::kBitwiseAND:   os << "&"; break;
    case Token::Type::kLogicalOR:    os << "||"; break;
    case Token::Type::kLogicalAND:   os << "&&"; break;
    case Token::Type::kLogicalNOT:   os << "!"; break;
    case Token::Type::kLargerThen:   os << ">"; break;
    case Token::Type::kSmallerThen:  os << "<"; break;
    case Token::Type::kLargerOrEqualThen:  os << ">="; break;
    case Token::Type::kSmallerOrEqualThen: os << "<="; break;
    case Token::Type::kEqual:        os << "=="; break;
    case Token::Type::kNotEqual:     os << "!="; break;
    case Token::Type::kParentLeft:   os << "("; break;
    case Token::Type::kParentRight:  os << ")"; break;
    case Token::Type::kQuestionmark:   os << "?"; break;
    case Token::Type::kColon:  os << ":"; break;
    case Token::Type::kComma:  os << ","; break;
  }
}

} // namespace greval

/* EOF */
