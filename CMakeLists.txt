# Copyright (C) 2013 Louis Hust. All Rights Reserved.

cmake_minimum_required(VERSION 2.6)
project(sql_parser)

# Project version number.
set (SQL_PARSER_VERSION_MAJOR 1)
set (SQL_PARSER_VERSION_MINOR 0)

# Set configure file
configure_file (
  "include/config.h.in"
  "${PROJECT_BINARY_DIR}/include/config.h"
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories(${PROJECT_BINARY_DIR}/include)
include_directories(include)

enable_testing()

# add subdirectory
add_subdirectory(src)
add_subdirectory(unit_test)

