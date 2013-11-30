# Copyright (C) 2013 Louis Hust. All Rights Reserved.

add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include)

#
# Unit Tests
#
macro(add_gtest name)
  add_executable(${name}_test ${name}_test.cxx)
  target_link_libraries(${name}_test gtest gtest_main ${ARGN})
  add_test(${name} ${name}_test)
endmacro()

add_gtest(first)
add_gtest(sql sql_parser_core)
add_gtest(mm sql_parser_core)

