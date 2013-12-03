/*
 * Copyright (C) 2013 Louis Hust. All Rights Reserved.
 * Memory Manager
 */

#include <malloc.h>
#include <string.h>
#include "mm.h"

void* my_malloc(size_t size)
{
  return malloc(size);
}

void my_free(void* p)
{
  return free(p);
}

mm_blk_node* mm_create_blk(size_t blk_size)
{
  mm_blk_node* blk_node;
  size_t all_size;

  all_size = blk_size + MAXALIGN(sizeof(mm_blk_node));

  blk_node = my_malloc(all_size);
  if (blk_node == NULL) {
    return NULL;
  }

  blk_node->free_ptr = (void*)blk_node + MAXALIGN(sizeof(mm_blk_node));
  blk_node->end_ptr = blk_node->free_ptr + blk_size - 1;
  blk_node->size = blk_size;
  blk_node->next = NULL;

  return blk_node;
}

memory_manager* mm_create(size_t blk_size)
{
  memory_manager *mm;
  mm_blk_node* blk_node;

  mm = my_malloc(sizeof(memory_manager));
  if (mm == NULL) {
    return NULL;
  }
  mm->first_blk_node = mm->current_blk_node = NULL;

  blk_size = MAXALIGN(blk_size);
  blk_size = MAX(blk_size, MM_MIN_BLK_SIZE);
  blk_node = mm_create_blk(blk_size);
  if (blk_node == NULL) {
    my_free (mm);
    return NULL;
  }
  mm->first_blk_node = mm->current_blk_node = blk_node;
  mm->blk_size = blk_size;
  return mm;
}

int mm_add_blk(memory_manager *mm, size_t size)
{
  mm_blk_node *node;
  size = MAXALIGN(size);
  size = MAX(mm->blk_size, size);

  node = mm_create_blk(size);
  if (node == NULL) {
    return 1;
  } else {
    mm->current_blk_node->next = node;
    mm->current_blk_node = node;
    return 0;
  }
}

int need_new_blk(mm_blk_node* node, size_t size)
{
  return  (node->free_ptr > node->end_ptr || (node->end_ptr - node->free_ptr + 1) < size);
}

void* mm_alloc(memory_manager* mm, size_t size)
{
  void* ret_ptr = NULL;
  mm_blk_node* node = mm->current_blk_node;
  if (need_new_blk(node, size)) {
    if (mm_add_blk(mm, size)) {
      return NULL;
    } else {
      return mm_alloc(mm, size);
    }
  } else {
    ret_ptr = node->free_ptr;
    node->free_ptr += MAXALIGN(size);
    return ret_ptr;
  }
}

void mm_destroy(memory_manager* mm)
{
  mm_blk_node* blk_node = mm->first_blk_node;
  mm_blk_node* free_node;
  while (blk_node) {
    free_node = blk_node;
    blk_node = free_node->next;
    my_free(free_node);
  }

  free(mm);
}

char* pstrdup(char* s)
{
  size_t len = strlen(s);
  char* ret = (char*)my_malloc(len + 1);
  memcpy(ret, s, len);
  ret[len] = '\0';
  return ret;
}
