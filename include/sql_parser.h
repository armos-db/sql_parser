/*
 * Copyright (C) 2013 Louis Hust. All Rights Reserved.
 */
#ifndef SQL_PARSER_H
#define SQL_PARSER_H

#include "sql_stmt.h"

#ifdef __cplusplus
extern "C" {
#endif

int parse_sql(const char* sql, size_t len, statement* stmt);


#ifdef __cplusplus
}
#endif

#endif
