/*
 * Copyright (C) 2013 Louis Hust. All Rights Reserved.
 * Memory Manager
 */
#ifndef SQL_PARSER_MM_H
#define SQL_PARSER_MM_H

#include "config.h"


typedef struct mm_block_node
{
  void *free_ptr;
  void *end_ptr;
  size_t size;
  struct mm_block_node *next;
} mm_blk_node;

typedef struct memory_manager{
  mm_blk_node* first_blk_node;
  mm_blk_node* current_blk_node;
  size_t blk_size;
} memory_manager;

#ifdef __cplusplus
extern "C" {
#endif

memory_manager* mm_create(size_t blk_size);
void* mm_alloc(memory_manager* mm, size_t size);
void mm_destroy(memory_manager* mm);

char* pstrdup(memory_manager* mm, char* s);

#ifdef __cplusplus
}
#endif


#endif
