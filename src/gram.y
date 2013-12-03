/*
 * Copyright (C) 2013 Louis Hust. All Rights Reserved.
 */
%define api.pure
%parse-param {struct pc_data *pp}

%{
#include <stdio.h>
%}


%union
{
  int           ival;
  char          *str;
  const char    *keyword;
}

%{
#include "scan.lex.h"
#include "parser.h"
# define YYLEX_PARAM pp->scaninfo
%}

%type <ival> Iconst

%token <ival> ICONST
%token <str>  FCONST



%%

Iconst: ICONST { $$ = $1; };

%%

int parse_sql(const char* sql, size_t len, statement* stmt)
{
  struct pc_data p = {NULL, stmt};
  int ret;

  /* set up scanner */
  if (yylex_init_extra(&p, &p.scaninfo)) {
    return 1;
  }

  /* set up input buffer instead of stdin */
  YY_BUFFER_STATE buffer_state;
  buffer_state = yy_scan_bytes(sql, len, p.scaninfo);
  ret = yyparse(&p);
  yy_delete_buffer(buffer_state, p.scaninfo);

  return ret;
}

