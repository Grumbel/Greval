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
file(GLOB EXPR_SOURCES src/*.cpp)
add_library(expr STATIC ${EXPR_SOURCES})
target_include_directories(expr PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/expr>
  $<INSTALL_INTERFACE:include>)
target_compile_options(expr PRIVATE ${TINYCMMC_WARNINGS_CXX_FLAGS})
set_target_properties(expr PROPERTIES PUBLIC_HEADER
  "${EXPR_HEADERS}")

if(BUILD_EXTRA)
  file(GLOB EXPR_EXTRA_SOURCES_CXX RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    extra/cmd_*.cpp)
  foreach(EXTRA_SOURCE ${EXPR_EXTRA_SOURCES_CXX})
    string(REGEX REPLACE ".*/cmd_\([^/]*\).cpp" "\\1" EXTRA_NAME ${EXTRA_SOURCE})
    set(EXTRA_TARGET "extra_${EXTRA_NAME}")
    add_executable(${EXTRA_TARGET} ${EXTRA_SOURCE})
    set_target_properties(${EXTRA_TARGET} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "extra/"
      OUTPUT_NAME "${PROJECT_NAME}-${EXTRA_NAME}")
    target_compile_options(${EXTRA_TARGET} PRIVATE ${TINYCMMC_WARNINGS_CXX_FLAGS})
    target_link_libraries(${EXTRA_TARGET} PRIVATE expr)

    install(TARGETS ${EXTRA_TARGET})
  endforeach(EXTRA_SOURCE)
endif()

if(BUILD_TESTS)
  find_package(GTest REQUIRED)

  # build test cases
  file(GLOB TEST_EXPR_SOURCES test/*_test.cpp)
  add_executable(test_expr ${TEST_EXPR_SOURCES})
  target_compile_options(test_expr PRIVATE ${WARNINGS_CXX_FLAGS})
  target_link_libraries(test_expr
    GTest::GTest
    GTest::Main
    expr)
endif()

tinycmmc_export_and_install_library(expr)

# EOF #
