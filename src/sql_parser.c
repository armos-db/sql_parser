#include <stdio.h>
#include "config.h"

int main (int argc, char *argv[])
{
  fprintf(stdout, "%s Version %d.%d\n",
      PROJECT_NAME,
      SQL_PARSER_VERSION_MAJOR,
      SQL_PARSER_VERSION_MINOR);
  return 0;
}

