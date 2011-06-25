#include <iostream>
#include <stdlib.h>
#include <boost/scoped_ptr.hpp>

#include "syntax_tree.hpp"
#include "lexer.hpp"
#include "parser.hpp"

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
        std::cout << expr->eval() << std::endl;
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
