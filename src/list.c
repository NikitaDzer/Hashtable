// Created by Nikita Dzer on 08.04.2022.

#include "../include/list.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef _ht_list_index_t index_t;
typedef _HtListPair Pair;


static const index_t LIST_NO_FREE       = -1;
static const index_t LIST_NO_PREV       = -1;
static const index_t LIST_NO_INDEX      = -1;
static const index_t LIST_NO_ITEMS      = -1;
static const index_t N_INITIAL_LIST_NODES = 16;
static const index_t LIST_NODES_MULTIPLIER = 2;


const _ht_list_index_t LIST_FAULT   = -1;
const _ht_list_index_t LIST_SUCCESS =  0;


inline static void fill_free(_HtListNode *restrict nodes, const index_t list_size)
{
    const index_t last_index = list_size * LIST_NODES_MULTIPLIER - 1;
    
    for (register index_t i = list_size; i < last_index; i++)
        nodes[i].next = i + 1;
   
    nodes[last_index].next = LIST_NO_FREE;
}

static index_t get_free(_HtList *restrict ht_list)
{
   if (ht_list->free != LIST_NO_FREE)
      return ht_list->free;
   
   const index_t size     = ht_list->size;
   const index_t capacity = size * LIST_NODES_MULTIPLIER;
   
   ht_list->nodes = (_HtListNode *)realloc(ht_list->nodes, capacity * sizeof(_HtListNode));
   
   if (ht_list->nodes == NULL)
      return LIST_FAULT;
   
    fill_free(ht_list->nodes, capacity);
    
    ht_list->free = size;
   
    return size;
}


_HtList* list_construct(_HtList *restrict ht_list)
{
    ht_list->nodes = (_HtListNode *)malloc(N_INITIAL_LIST_NODES * sizeof(_HtListNode));
   
   if (ht_list->nodes == NULL)
      return NULL;
    
    ht_list->free = 0;
    ht_list->head = LIST_NO_ITEMS;
    ht_list->size = 0;
    
    for (register index_t i = 0; i < N_INITIAL_LIST_NODES - 1; i++)
        ht_list->nodes[i].next = i + 1;
    
    ht_list->nodes[N_INITIAL_LIST_NODES - 1].next = LIST_NO_FREE;
   
    return ht_list;
}

inline void list_destruct(_HtList *restrict ht_list)
{
   if (ht_list->nodes != NULL)
      free(ht_list->nodes);
}

HtValue* list_insert(_HtList *restrict ht_list, const char *restrict key, const HtValue *restrict ht_value)
{
   const index_t free = get_free(ht_list);
   
   if (free == LIST_FAULT)
      return NULL;
   
   _HtListNode *restrict nodes = ht_list->nodes;
   
   strncpy(nodes[free].pair.key, key, HT_MAX_N_KEY_CHARS);
   nodes[free].pair.value = *ht_value;
   
   if (ht_list->size == 0)
      ht_list->head = free;
   
   ht_list->free  = nodes[free].next;
   ht_list->head  = free;
   ht_list->size += 1;
   
   return &nodes[free].pair.value;
}

HtValue* list_remove(_HtList *restrict ht_list, const char *restrict key)
{
   _HtListNode *restrict nodes = ht_list->nodes;
 
   register index_t index = LIST_NO_FREE;
   register index_t prev  = LIST_NO_FREE;

   for (register index_t i = ht_list->head; i != LIST_NO_FREE; prev = i, i = nodes[i].next) // rename constant
       if (strncmp(nodes[i].pair.key, key, HT_MAX_N_KEY_CHARS) == 0)
       {
           index = i;
           break;
       }
   
   if (index == LIST_NO_FREE)
       return NULL;
   
   if (ht_list->head == index)
       ht_list->head = nodes[index].next;
   else
       nodes[prev].next = nodes[index].next;
    
    nodes[index].next = ht_list->free;
    
    ht_list->free  = index;
    ht_list->size -= 1;
   
    return &nodes[index].pair.value;
}

HtValue* list_find_value(const _HtList *restrict ht_list, const char *restrict key)
{
   _HtListNode *restrict nodes = ht_list->nodes;
   
  for (register index_t i = ht_list->head; i != LIST_NO_FREE; i = nodes[i].next)
     if (strncmp(nodes[i].pair.key, key, HT_MAX_N_KEY_CHARS) == 0)
        return &nodes[i].pair.value;
   
   return NULL;
}