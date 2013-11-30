# Copyright (C) 2013 Louis Hust. All Rights Reserved.


add_custom_target(Parser)

set(GEN_SOURCES
  ${CMAKE_BINARY_DIR}/src/scan.lex.c
  ${CMAKE_BINARY_DIR}/include/scan.lex.h
  ${CMAKE_BINARY_DIR}/src/gram.tab.c
  ${CMAKE_BINARY_DIR}/include/gram.tab.h
)

# add the command to generate the source code
add_custom_command(
  TARGET Parser
  COMMAND flex -o ${CMAKE_CURRENT_BINARY_DIR}/scan.lex.c
  --header-file=${PROJECT_BINARY_DIR}/include/scan.lex.h
  ${CMAKE_SOURCE_DIR}/src/scan.l
)

add_custom_command(
  TARGET Parser
  COMMAND bison -d -o ${PROJECT_BINARY_DIR}/src/gram.tab.c ${CMAKE_SOURCE_DIR}/src/gram.y
  COMMAND mv ${PROJECT_BINARY_DIR}/src/gram.tab.h ${PROJECT_BINARY_DIR}/include/
)

set_source_files_properties(${GEN_SOURCES} GENERATED)

# create libraries
add_library(sql_parser_core SHARED
  ${CMAKE_CURRENT_BINARY_DIR}/scan.lex.c ${CMAKE_CURRENT_BINARY_DIR}/gram.tab.c mm.c)
add_dependencies(sql_parser_core Parser)
target_link_libraries(sql_parser_core fl)

# add the executable
add_executable(sql_parser sql_parser.c)
target_link_libraries(sql_parser sql_parser_core)

# add the install targets
install (TARGETS sql_parser DESTINATION bin)
