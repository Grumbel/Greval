# Expr - A simple toy programming language
# Copyright (C) 2015 Ingo Ruhnke <grumbel@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.0)
project(expr VERSION 0.1.0)

add_compile_options(-std=c++1y)

set(WARNINGS 0 CACHE BOOL "Switch on extra warnings")

if(WARNINGS)
  set(WARNINGS_CXX_FLAGS
    -pedantic -Wall -Wextra -Wno-c++0x-compat -Wnon-virtual-dtor -Weffc++
    -Wconversion -Werror -Wshadow -Wcast-qual -Winit-self -Wno-unused-parameter)
  # -Winline -Wfloat-equal -Wunreachable-code
endif()

find_package(Threads REQUIRED)

include_directories(src/)

# build expr
add_library(libexpr STATIC
  src/lexer.cpp
  src/parser.cpp
  src/token.cpp
  src/value.cpp
  src/environment.cpp
  src/print_visitor.cpp
  src/eval_visitor.cpp)
set_target_properties(libexpr PROPERTIES OUTPUT_NAME "expr")

add_executable(expr
  src/expr.cpp)
target_link_libraries(expr libexpr)

add_executable(lexer_test src/lexer_test.cpp)
target_link_libraries(lexer_test libexpr)

# build googletest
include_directories(SYSTEM external/googletest/include/)
add_library(gtest STATIC ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/src/gtest-all.cc)
target_include_directories(gtest SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/)
add_library(gtest_main STATIC ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/src/gtest_main.cc)

# build test cases
file(GLOB TEST_EXPR_SOURCES test/*_test.cpp)
add_executable(test_expr ${TEST_EXPR_SOURCES})
target_compile_options(test_expr PRIVATE ${WARNINGS_CXX_FLAGS})
target_link_libraries(test_expr
  gtest gtest_main
  libexpr
  ${CMAKE_THREAD_LIBS_INIT})

# EOF #
