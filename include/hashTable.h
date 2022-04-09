// Created by Nikita Dzer on 09.04.2022.

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "ht_value.h"

#define N_HASHTABLE_LISTS 65536

#include "../list/include/list.h"

typedef struct HashTable
{
   List lists[N_HASHTABLE_LISTS];
} HashTable;

HashTable* construct_hashTable(void);

void       destruct_hashTable(HashTable *const p_hashTable);

void hashTable_insert(HashTable *const p_hashTable, const char *const key, const ht_value_t value);

void hashTable_delete(HashTable *const p_hashTable, const char *const key);

ht_value_t* hashTable_search(const HashTable *const p_hastTable, const char *const key);

#endif // HASHTABLE_H
