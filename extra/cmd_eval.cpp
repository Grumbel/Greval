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

#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <memory>

#include <expr/eval_visitor.hpp>
#include <expr/print_visitor.hpp>
#include <expr/lexer.hpp>
#include <expr/parser.hpp>
#include <expr/syntax_tree.hpp>

namespace expr {

Value script_sin(std::vector<Value> const& args)
{
  if (args.size() != 1)
  {
    throw std::runtime_error("invalid number of arguments");
  }
  else
  {
    return Value::real(sinf(args[0].get_real()));
  }
}

Value script_sqrt(std::vector<Value> const& args)
{
  if (args.size() != 1)
  {
    throw std::runtime_error("invalid number of arguments");
  }
  else
  {
    return Value::real(sqrtf(args[0].get_real()));
  }
}

Value script_cos(std::vector<Value> const& args)
{
  if (args.size() != 1)
  {
    throw std::runtime_error("invalid number of arguments");
  }
  else
  {
    return Value::real(cosf(args[0].get_real()));
  }
}

int eval_run(int argc, char** argv)
{
  if (argc < 2)
  {
    std::cerr << "error: argument required" << std::endl;
    return EXIT_FAILURE;
  }
  else
  {
    try
    {
      std::string args;
      for(int i = 1; i < argc; ++i)
      {
        args += argv[i];
      }
      Lexer lexer(args);

      if (false)
      {
        while(!lexer.is_eof())
        {
          Token token = lexer.get_token();
          std::cout << "token: " << token << std::endl;
        }
      }
      else
      {
        Parser parser(lexer);
        std::unique_ptr<Expr> expr(parser.parse());
        Environment env;
        env.bind_function("cos", script_cos);
        env.bind_function("sin", script_sin);
        env.bind_function("sqrt", script_sqrt);
        env.bind_variable("pi", Value::real(static_cast<float>(M_PI)));

        std::ostringstream str;
        PrintVisitor print_visitor(str);
        expr->accept(print_visitor);
        std::cout << "Syntax Tree: " << str.str() << std::endl;

        EvalVisitor eval_visitor(env);
        expr->accept(eval_visitor);
        std::cout << "EvalVisitor: " << eval_visitor.get_result() << std::endl;
      }
    }
    catch(std::exception const& err)
    {
      std::cerr << "error: " << err.what() << std::endl;
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }
}

} // namespace expr

int main(int argc, char** argv)
{
  return expr::eval_run(argc, argv);
}

/* EOF */
