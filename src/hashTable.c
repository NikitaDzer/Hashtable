// Created by Nikita Dzer on 09.04.2022.

#include <stdlib.h>
#include <string.h>
#include "../include/hashTable.h"
#include "../include/hash.h"

typedef unsigned short index_t;

inline static index_t hash(const char *const key)
{
   return qhash(key, strlen(key));
}

HashTable* construct_hashTable(void)
{
   HashTable *const p_hashTable = (HashTable *)calloc(1, sizeof(HashTable));
   
   if (p_hashTable == NULL)
      return NULL;
   
   List *const lists = p_hashTable->lists;
   
   for (unsigned long long i = 0; i < N_HASHTABLE_LISTS; i++)
      if (list_construct(lists + i) == LIST_FAULT)
      {
         free(p_hashTable);
         return NULL;
      }
   
   return p_hashTable;
}

void       destruct_hashTable(HashTable *const p_hashTable)
{
   List *const lists = p_hashTable->lists;
   
#ifdef HASHTABLE_ANTI_FOOL
   
   if (p_hashTable != NULL)
   {
      for (unsigned long long i = 0; i < N_HASHTABLE_LISTS; i++)
         list_destruct(lists + i);
      
      free(p_hashTable);
   }
   
#else // !HASHTABLE_ANTI_FOOL

   for (unsigned long long i = 0; i < N_HASHTABLE_LISTS; i++)
      list_destruct(lists + i);
   
   free(p_hashTable);
   
#endif // !HASHTABLE_ANTI_FOOL
}

ht_value_t* hashTable_search(const HashTable *const p_hastTable, const char *const key)
{
   list_item_t *const p_item = list_find_item_address(p_hastTable->lists + hash(key), key);
   
   if (p_item == NULL)
      return NULL;
   
   return &p_item->value;
}

void hashTable_insert(HashTable *const p_hashTable, const char *const key, const ht_value_t value)
{
   List *const p_list = p_hashTable->lists + hash(key);
   
   if (list_find_item_address(p_list, key) == NULL)
      list_pushFront(p_list, (list_item_t){ .key = key, .value = value });
}

void hashTable_delete(HashTable *const p_hashTable, const char *const key)
{
   list_extract(p_hashTable->lists + hash(key), key);
}