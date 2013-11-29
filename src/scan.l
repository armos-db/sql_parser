%{
/*
 * Copyright (C) 2013 Louis Hust. All Rights Reserved.
 */
#include <stdio.h>
#include "gram.tab.h"
#include "parser.h"

/*
 *  Set the type of YYSTYPE
 */
/* #define YYSTYPE core_YYSTYPE */

void yyerror(const char*);

static int process_integer_literal(const char *token, YYSTYPE *lval);

%}

%option bison-bridge
%option yylineno
%option noyywrap
%option reentrant

%x xc

space           [ \t\n\r\f]
horiz_space     [ \t\f]
newline         [\n\r]
non_newline     [^\n\r]

/* normal comment '--' */
comment         ("--"{non_newline}*)

whitespace      ({space}+|{comment})

op_chars        [\~\!\@\#\^\&\|\`\?\+\-\*\/\%\<\>\=]

/* C-style comment TODO: add MySQL executable comment */
xcstart         \/\*{op_chars}*
xcstop          \*+\/
xcinside        .*

/* Numeric type */
digit           [0-9]
integer         {digit}+
decimal         (({digit}*\.{digit}+)|({digit}+\.{digit}*))
decimalfail     {digit}+\.\.

/* identifier */
ident_start     [A-Za-z\200-\377_]
ident_cont      [A-Za-z\200-\377_0-9\$]

identifier      {ident_start}{ident_cont}*


%%

{whitespace}    { /* ignore */ }

 /* C-styple comment */
{xcstart}       { BEGIN(xc); }
<xc>{xcstop}    { BEGIN(INITIAL); }
<xc>{xcinside}  { /* ignore */ }
<xc><<EOF>>     { yyerror("unterminated /* comment"); }

{integer}       { return process_integer_literal(yytext, yylval); }
{decimal}       { yylval->str = yytext; return FCONST; }


%%

void yyerror(const char* s)
{
 fprintf(stdout, "scan.l error:%s.\n", s);
}

static int
process_integer_literal(const char *token, YYSTYPE *lval)
{
  long  val;
  char  *endptr;

  errno = 0;
  val = strtol(token, &endptr, 10);
  if (*endptr != '\0' || errno == ERANGE
#ifdef HAVE_LONG_INT_64
    /* if long > 32 bits, check for overflow of int4 */
    || val != (long) ((int32) val)
#endif
    )
  {
    /* integer too large, treat it as a float */
    lval->str = (char*)token;
    return FCONST;
  }
  lval->ival = val;
  return ICONST;
}
