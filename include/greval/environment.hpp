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

#ifndef HEADER_ENVIRONMENT_HPP
#define HEADER_ENVIRONMENT_HPP

#include <functional>
#include <vector>
#include <map>

#include "value.hpp"

namespace greval {

typedef std::function<Value(std::vector<Value> const&)> ScriptFunction;

class Environment
{
private:
  typedef std::map<std::string, ScriptFunction> Functions;
  Functions m_functions;
  typedef std::map<std::string, Value> Variables;
  Variables m_variables;

public:
  Environment();

  void bind_variable(std::string const& name, Value const& value);
  void bind_function(std::string const& name, ScriptFunction const& value);

  Value lookup_variable(std::string const& name) const;
  ScriptFunction lookup_function(std::string const& name) const;

private:
  Environment(Environment const&);
  Environment& operator=(Environment const&);
};

} // namespace greval

#endif

/* EOF */
