#include <iostream>
#include <stdlib.h>

#include "lexer.hpp"

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
      while(!lexer.is_eof())
      {
        std::cout << lexer.get_token() << std::endl;
      }
      return EXIT_SUCCESS;
    }
    catch(const std::exception& err)
    {
      std::cerr << "error: " << err.what() << std::endl;
      return EXIT_FAILURE;
    }
  }
}

/* EOF */
