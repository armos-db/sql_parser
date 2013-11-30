/*
 * Copyright (C) 2013 Louis Hust. All Rights Reserved.
 */
#ifndef SQL_PARSER_PARSER_H
#define SQL_PARSER_PARSER_H

#include "sql_stmt.h"
#include "mm.h"

/* personal data */
struct pc_data
{
  yyscan_t    scaninfo;
  memory_manager *mm;
  statement   *stmt;
};

#endif
