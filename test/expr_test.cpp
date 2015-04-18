#include <memory>
#include <gtest/gtest.h>

#include "eval_visitor.hpp"
#include "print_visitor.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "syntax_tree.hpp"

Value script_plus(const std::vector<Value>& args)
{
  int result = 0;
  for(const auto& v : args)
  {
    result += v.get_integer();
  }
  return Value::integer(result);
}

Value script_plus_one(const std::vector<Value>& args)
{
  return Value::integer(args[0].get_integer() + 1);
}

Value eval_expr(const std::string& text)
{
  Lexer lexer(text);
  Parser parser(lexer);
  std::unique_ptr<Expr> expr(parser.parse());
  Environment env;
  env.bind_function("plus", script_plus);
  env.bind_function("plus_one", script_plus_one);

  env.bind_variable("A", Value::integer(2));
  env.bind_variable("B", Value::integer(40));
  env.bind_variable("pi", Value::real(3.1415927f));

  EvalVisitor eval_visitor(env);
  expr->accept(eval_visitor);
  return eval_visitor.get_result();
}

TEST(ExprTest, test)
{
  // normal expressions
  EXPECT_EQ(Value::integer(18), eval_expr("5+6+7"));
  EXPECT_EQ(Value::integer(25), eval_expr("(5+6)+7*2"));
  EXPECT_EQ(Value::integer(5), eval_expr("5+11/12*3"));
  EXPECT_EQ(Value::real(7.75), eval_expr("5.0+11.0/12.0*3.0"));

  // boolean
  EXPECT_EQ(Value::integer(1), eval_expr("1243<23222"));
  EXPECT_EQ(Value::integer(1), eval_expr("!(1243>23222)"));

  // unary expressions
  EXPECT_EQ(Value::integer(-45), eval_expr("-45"));
  EXPECT_EQ(Value::integer(45), eval_expr("--45"));
  EXPECT_EQ(Value::integer(-45), eval_expr("-+-+-45"));

  // conditionals
  EXPECT_EQ(Value::integer(1234), eval_expr("(5>2)?1234:5678"));
  EXPECT_EQ(Value::integer(5678), eval_expr("(5<2)?1234:5678"));

  // function calls
  EXPECT_EQ(Value::integer(11), eval_expr("plus_one(10)"));
  EXPECT_EQ(Value::integer(20), eval_expr("plus(10, 10)"));

  // variables
  EXPECT_EQ(Value::integer(42), eval_expr("A + B"));
  EXPECT_EQ(Value::real(3.1415927f), eval_expr("pi"));
}

/* EOF */
