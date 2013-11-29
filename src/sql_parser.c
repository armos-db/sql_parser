/**
 * Copyright (C) 2013 Louis Hust. All Rights Reserved.
 */

#include <stdio.h>
#include "config.h"
#include "sql_parser.h"

int main (int argc, char *argv[])
{
  fprintf(stdout, "%s Version %d.%d\n",
      PROJECT_NAME,
      SQL_PARSER_VERSION_MAJOR,
      SQL_PARSER_VERSION_MINOR);
  parse_sql("123", 3, NULL);
  return 0;
}

