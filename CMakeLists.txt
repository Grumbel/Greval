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

include(mk/cmake/TinyCMMC.cmake)

# build expr
file(GLOB EXPR_HEADERS include/expr/*.hpp)
add_library(expr STATIC
  src/lexer.cpp
  src/parser.cpp
  src/token.cpp
  src/value.cpp
  src/environment.cpp
  src/print_visitor.cpp
  src/eval_visitor.cpp)
target_include_directories(expr PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/expr>
  $<INSTALL_INTERFACE:include>)
target_compile_options(expr ${TINYCMMC_WARNINGS_CXX_FLAGS})
set_target_properties(expr PROPERTIES PUBLIC_HEADER
  "${EXPR_HEADERS}")

add_executable(expr_exe
  src/expr.cpp)
set_target_properties(expr_exe PROPERTIES OUTPUT_NAME "expr")
target_link_libraries(expr_exe expr)
target_compile_options(expr_exe ${TINYCMMC_WARNINGS_CXX_FLAGS})

add_executable(lexer_test src/lexer_test.cpp)
target_link_libraries(lexer_test expr)

if(BUILD_TESTS)
  find_package(GTest REQUIRED)

  # build test cases
  file(GLOB TEST_EXPR_SOURCES test/*_test.cpp)
  add_executable(test_expr ${TEST_EXPR_SOURCES})
  target_compile_options(test_expr PRIVATE ${WARNINGS_CXX_FLAGS})
  target_link_libraries(test_expr
    GTest::GTest GTest::Main
    expr)
endif()

install(TARGETS expr_exe)
tinycmmc_export_and_install_library(expr)

# EOF #
