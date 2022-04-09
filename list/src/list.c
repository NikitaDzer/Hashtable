// Created by Nikita Dzer on 08.04.2022.

#include "../include/list.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef list_index_t index_t;
typedef list_item_t  item_t;

typedef struct pair_index_prev
{
   const index_t index;
   const index_t prev;
} pair_index_prev;


static const index_t LIST_NO_FREE       = -1;
static const index_t LIST_NO_PREV       = -1;
static const index_t LIST_NO_INDEX      = -1;
static const index_t LIST_NO_ITEMS      = -1;
static const index_t N_LIST_ADD_NODES   = 64;

const list_index_t LIST_FAULT   = -1;
const list_index_t LIST_SUCCESS =  0;



static void fill_free(ListNode *const nodes, const index_t list_capacity)
{
   const index_t list_size = list_capacity - N_LIST_ADD_NODES;
   
   memset(nodes + list_size, 0, sizeof(ht_value_t) * (list_capacity - list_size));
   
   for (index_t i = list_size; i < list_capacity - 1; i++)
      nodes[i].next = i + 1;
   
   nodes[list_capacity - 1].next = LIST_NO_FREE;
}

static index_t get_free(List *const p_list)
{
   if (p_list->free != LIST_NO_FREE)
      return p_list->free;
   
   const index_t        size     = p_list->size;
   const index_t        capacity = size + N_LIST_ADD_NODES;
   ListNode      *const nodes    = (ListNode *)realloc(p_list->nodes, capacity * sizeof(ListNode));
   
   if (nodes == NULL)
      return LIST_FAULT;
   
   nodes[p_list->tail].next = size;
   p_list->free             = size;
   p_list->nodes            = nodes;
   
   fill_free(nodes, capacity);
   
   return size;
}



index_t list_construct(List *const p_list)
{
#ifdef LIST_ANTI_FOOL
   if (p_list == NULL)
      return LIST_FAULT;
#endif // LIST_ANTI_FOOL
   
   ListNode *const nodes = (ListNode *)calloc(N_LIST_ADD_NODES, sizeof(ListNode));
   
   if (nodes == NULL)
      return LIST_FAULT;
   
   p_list->head  = LIST_NO_ITEMS;
   p_list->tail  = LIST_NO_ITEMS;
   p_list->free  = 0;
   p_list->size  = 0;
   p_list->nodes = nodes;
   
   fill_free(nodes, N_LIST_ADD_NODES);
   
   return LIST_SUCCESS;
}

void list_destruct(List *const p_list)
{
#ifdef LIST_ANTI_FOOL
   if (p_list != NULL && p_list->nodes != NULL)
      free(p_list->nodes);
#else // !LIST_ANTI_FOOL
   if (p_list->nodes != NULL)
      free(p_list->nodes);
#endif // !LIST_ANTI_FOOL
}

index_t list_pushFront(List *const p_list, const item_t item)
{
#ifdef    LIST_ANTI_FOOL
   if (p_list == nullptr)
      return LIST_FAULT;
   
   if (verify_list(p_list))
      return LIST_FAULT;
#endif // LIST_ANTI_FOOL

   const index_t free = get_free(p_list);
   
   if (free == LIST_FAULT)
      return LIST_FAULT;
   
   ListNode      *const nodes    = p_list->nodes;
   const index_t        nextFree = nodes[free].next;
   
   nodes[free].item = item;
   nodes[free].next = p_list->head;
   
   if (p_list->size == 0)
      p_list->tail = free;
   
   p_list->free  = nodes[free].next;
   p_list->head  = free;
   p_list->size += 1;
   
   return free;
}

ht_value_t *list_extract(List *const p_list, const char *const key)
{
   ListNode *const nodes = p_list->nodes;
   index_t         index = LIST_NO_INDEX;
   index_t         prev  = LIST_NO_PREV;
   index_t         i     = p_list->head;
   
   if (i == LIST_NO_ITEMS)
       return NULL;

   while (true)
   {
      if (strncmp(nodes[i].item.key, key, N_KEY_CHARS) == 0)
      {
         index = i;
         break;
      }
      
      if (i == p_list->tail)
         break;
      
      prev = i;
      i    = nodes[i].next;
   }
   
   if (index == LIST_NO_INDEX)
      return NULL;
   
   const index_t next = nodes[index].next;
   
   nodes[index].next = p_list->free;
   
   if (prev != LIST_NO_PREV)
      nodes[prev].next = next;
   else
      p_list->tail = next;
   
   if (p_list->head == index)
      p_list->head = prev;
   
   p_list->free  = index;
   p_list->size -= 1;
   
   return &nodes[index].item.value;
}

item_t *list_find_item_address(const List *const p_list, const char *const key)
{
   ListNode *const nodes = p_list->nodes;
   
   if (p_list->size >= 1)
   {
      for (index_t i = p_list->head; i != p_list->tail; i = nodes[i].next)
      {
         if (strncmp(nodes[i].item.key, key, N_KEY_CHARS) == 0)
            return &nodes[i].item;
      }
   
      if (strncmp(nodes[p_list->tail].item.key, key, N_KEY_CHARS) == 0)
         return &nodes[p_list->tail].item;
   }
   
   return NULL;
}