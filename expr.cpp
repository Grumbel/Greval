#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <boost/scoped_ptr.hpp>
#include <sstream>

#include "eval_visitor.hpp"
#include "print_visitor.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "syntax_tree.hpp"

Value script_sin(const std::vector<Value>& args)
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

Value script_sqrt(const std::vector<Value>& args)
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

Value script_cos(const std::vector<Value>& args)
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

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "error: argument required" << std::endl;
    return EXIT_FAILURE;
  }
  else
  {
    try 
    {
      Lexer lexer(argv[1]);
    
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
        boost::scoped_ptr<Expr> expr(parser.parse());
        Environment env;
        env.bind_function("cos", script_cos);
        env.bind_function("sin", script_sin);
        env.bind_function("sqrt", script_sqrt);
        env.bind_variable("pi", Value::real(static_cast<float>(M_PI)));

        std::ostringstream str;
        PrintVisitor print_visitor(str);
        expr->accept(print_visitor);
        std::cout << "Syntax Tree: " << str.str() << std::endl;

        std::cout << "Expr::eval(): " << expr->eval(env) << std::endl;

        EvalVisitor eval_visitor(env);
        expr->accept(eval_visitor);
        std::cout << "EvalVisitor:  " << eval_visitor.get_result() << std::endl;
      }
    }
    catch(const std::exception& err)
    {
      std::cerr << "error: " << err.what() << std::endl;
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }
}

/* EOF */
