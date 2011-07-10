//  Expr - A simple toy programming language
//  Copyright (C) 2011 Ingo Ruhnke <grumbel@gmail.com>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "environment.hpp"

Environment::Environment() :
  m_functions(),
  m_variables()
{
}

void
Environment::bind_variable(const std::string& name, const Value& value)
{
  m_variables.insert(std::pair<std::string, Value>(name, value));
}

void
Environment::bind_function(const std::string& name, const ScriptFunction& func)
{
  m_functions.insert(std::pair<std::string, ScriptFunction>(name, func));
}

Value
Environment::lookup_variable(const std::string& name) const
{
  Variables::const_iterator it = m_variables.find(name);
  if (it == m_variables.end())
  {
    throw std::runtime_error("variable lookup failure: " + name);
  }
  else
  {
    return it->second;
  }
}

ScriptFunction
Environment::lookup_function(const std::string& name) const
{
  Functions::const_iterator it = m_functions.find(name);
  if (it == m_functions.end())
  {
    throw std::runtime_error("function lookup failure: " + name);
  }
  else
  {
    return it->second;
  }
}

/* EOF */
