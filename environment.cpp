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
