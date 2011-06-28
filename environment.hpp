#ifndef HEADER_ENVIRONMENT_HPP
#define HEADER_ENVIRONMENT_HPP

#include <boost/function.hpp>
#include <vector>
#include <map>

#include "value.hpp"

typedef boost::function<Value(const std::vector<Value>&)> ScriptFunction;

class Environment
{
private:
  typedef std::map<std::string, ScriptFunction> Functions;
  Functions m_functions;
  typedef std::map<std::string, Value> Variables;
  Variables m_variables;

public:
  Environment();

  void bind_variable(const std::string& name, const Value& value);
  void bind_function(const std::string& name, const ScriptFunction& value);
  
  Value lookup_variable(const std::string& name) const;
  ScriptFunction lookup_function(const std::string& name) const;

private:
  Environment(const Environment&);
  Environment& operator=(const Environment&);
};

#endif

/* EOF */
