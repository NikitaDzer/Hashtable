// Created by Nikita Dzer on 08.04.2022.

#ifndef HASHTABLE_LIST_H
#define HASHTABLE_LIST_H

#include "../../include/ht_value.h"

typedef signed long long int list_index_t;

typedef struct list_item_t
{
   const char *key;
   ht_value_t  value;
} list_item_t;

typedef struct ListNode
{
   list_item_t  item;
   list_index_t next;
} ListNode;

typedef struct List
{
   list_index_t  head;
   list_index_t  tail;
   list_index_t  free;
   list_index_t  size;
   ListNode     *nodes;
} List;

#include "../../include/hashTable.h"

extern const list_index_t LIST_FAULT;
extern const list_index_t LIST_SUCCESS;


list_index_t list_construct(List *const p_list);

void         list_destruct (List *const p_list);

list_index_t list_pushFront(List *const p_list, const list_item_t item);

ht_value_t *list_extract(List *const p_list, const char *const key);

list_item_t *list_find_item_address(const List *const p_list, const char *const key);

#endif // HASHTABLE_LIST_H
