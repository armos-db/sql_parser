%{
/*
 * Copyright (C) 2013 Louis Hust. All Rights Reserved.
 */
#include <stdio.h>
#include "gram.tab.h"
#include "parser.h"


void yyerror(const char*);


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

%{
  struct pc_data *pp = yyextra;
%}

{whitespace}    { /* ignore */ }

 /* C-styple comment */
{xcstart}       { BEGIN(xc); }
<xc>{xcstop}    { BEGIN(INITIAL); }
<xc>{xcinside}  { /* ignore */ }
<xc><<EOF>>     { yyerror("unterminated /* comment"); }

{integer}       { yylval->str = pstrdup(yytext); return ICONST;}
{decimal}       { yylval->str = pstrdup(yytext); return FCONST; }


%%

void yyerror(const char* s)
{
 fprintf(stdout, "scan.l error:%s.\n", s);
}
