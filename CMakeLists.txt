# greval - A simple toy programming language
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
project(greval VERSION 0.1.0)

include(mk/cmake/TinyCMMC.cmake)

# build greval
file(GLOB GREVAL_HEADERS include/greval/*.hpp)
file(GLOB GREVAL_SOURCES src/*.cpp)
add_library(greval STATIC ${GREVAL_SOURCES})
target_include_directories(greval PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/greval>
  $<INSTALL_INTERFACE:include>)
target_compile_options(greval PRIVATE ${TINYCMMC_WARNINGS_CXX_FLAGS})
set_target_properties(greval PROPERTIES PUBLIC_HEADER
  "${GREVAL_HEADERS}")

if(BUILD_EXTRA)
  file(GLOB GREVAL_EXTRA_SOURCES_CXX RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    extra/cmd_*.cpp)
  foreach(EXTRA_SOURCE ${GREVAL_EXTRA_SOURCES_CXX})
    string(REGEX REPLACE ".*/cmd_\([^/]*\).cpp" "\\1" EXTRA_NAME ${EXTRA_SOURCE})
    set(EXTRA_TARGET "extra_${EXTRA_NAME}")
    add_executable(${EXTRA_TARGET} ${EXTRA_SOURCE})
    set_target_properties(${EXTRA_TARGET} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "extra/"
      OUTPUT_NAME "${PROJECT_NAME}-${EXTRA_NAME}")
    target_compile_options(${EXTRA_TARGET} PRIVATE ${TINYCMMC_WARNINGS_CXX_FLAGS})
    target_link_libraries(${EXTRA_TARGET} PRIVATE greval)

    install(TARGETS ${EXTRA_TARGET})
  endforeach(EXTRA_SOURCE)
endif()

if(BUILD_TESTS)
  find_package(GTest REQUIRED)

  # build test cases
  file(GLOB TEST_GREVAL_SOURCES test/*_test.cpp)
  add_executable(test_greval ${TEST_GREVAL_SOURCES})
  target_compile_options(test_greval PRIVATE ${WARNINGS_CXX_FLAGS})
  target_link_libraries(test_greval
    GTest::GTest
    GTest::Main
    greval)
endif()

tinycmmc_export_and_install_library(greval)

# EOF #
