#include <memory>
#include <gtest/gtest.h>

#include "eval_visitor.hpp"
#include "print_visitor.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "syntax_tree.hpp"

Value eval_expr(const std::string& text)
{
  Lexer lexer(text);
  Parser parser(lexer);
  std::unique_ptr<Expr> expr(parser.parse());
  Environment env;
  EvalVisitor eval_visitor(env);
  expr->accept(eval_visitor);
  return eval_visitor.get_result();
}

TEST(ExprTest, test)
{
  EXPECT_EQ(Value::integer(18), eval_expr("5+6+7"));
  EXPECT_EQ(Value::integer(25), eval_expr("(5+6)+7*2"));
  EXPECT_EQ(Value::integer(5), eval_expr("5+11/12*3"));
  EXPECT_EQ(Value::real(7.75), eval_expr("5.0+11.0/12.0*3.0"));
  EXPECT_EQ(Value::integer(1), eval_expr("1243<23222"));
  EXPECT_EQ(Value::integer(1), eval_expr("!(1243>23222)"));
  EXPECT_EQ(Value::integer(1234), eval_expr("(5>2)?1234:5678"));
  EXPECT_EQ(Value::integer(5678), eval_expr("(5<2)?1234:5678"));
}

/* EOF */
