// Created by Nikita Dzer on 09.04.2022.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/hashtable.h"
#include "../include/hash.h"

#if   _HT_N_HASHTABLE_LISTS == (UCHAR_MAX + 1)
typedef unsigned char  ht_index_t;
#elif _HT_N_HASHTABLE_LISTS == (USHRT_MAX + 1)
typedef unsigned short ht_index_t;
#elif _HT_N_HASHTABLE_LISTS == (UINT_MAX  + 1)
typedef unsigned int   ht_index_t;
#elif _HT_N_HASHTABLE_LISTS == (ULONG_MAX + 1)
typedef unsigned long  ht_index_t;
#endif // _HT_N_HASHTABLE_LISTS == (ULONG_MAX + 1)

inline static ht_index_t hash(const char *const key)
{
   return qhash(key, strlen(key));
}

HtHashtable* construct_hashtable(void)
{
    HtHashtable *restrict ht_hashTable = (HtHashtable *)malloc(sizeof(HtHashtable));
   
    if (ht_hashTable == NULL)
        return NULL;
   
    for (register ht_index_t i = 0;; i++)
    {
        if (list_construct(ht_hashTable->lists + i) == NULL)
        {
            destruct_hashtable(ht_hashTable);
            return NULL;
        }
    
        if (i == _HT_N_HASHTABLE_LISTS - 1)
            return ht_hashTable;
    }
}

void destruct_hashtable(HtHashtable *restrict ht_hashtable)
{
    if (ht_hashtable != NULL)
    {
        for (register ht_index_t i = 0;; i++)
        {
            list_destruct(ht_hashtable->lists + i);
            
            if (i == _HT_N_HASHTABLE_LISTS - 1)
                break;
        }
        
        free(ht_hashtable);
    }
}


HtValue* hashtable_insert(      HtHashtable *restrict ht_hashtable, const char *restrict key, const HtValue *restrict ht_value)
{
    if (ht_hashtable == NULL || key == NULL || ht_value == NULL)
        return NULL;
    
    _HtList *restrict ht_list = ht_hashtable->lists + hash(key);
    
    if (list_find_value(ht_list, key) != NULL)
        return NULL;
    
    return list_insert(ht_list, key, ht_value);           // error proc
}

HtValue* hashtable_remove(      HtHashtable *restrict ht_hashtable, const char *restrict key)
{
    if (ht_hashtable == NULL || key == NULL)
        return NULL;
    
    return list_remove(ht_hashtable->lists + hash(key), key);
}

HtValue* hashtable_search(const HtHashtable *restrict ht_hashtable, const char *restrict key)
{
    if (ht_hashtable == NULL || key == NULL)
        return NULL;
    
    return list_find_value(ht_hashtable->lists + hash(key), key);
}

HtValue* hashtable_clear (      HtHashtable *restrict ht_hashtable)
{
    return NULL;
}