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
