// Created by Nikita Dzer on 09.04.2022.

#include <stdlib.h>
#include <string.h>
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

#undef construct_hashtable
#undef destruct_hashtable
#undef hashtable_insert
#undef hashtable_remove
#undef hashtable_search
#undef verify_hashtable

HtResult ht_result = HT_SUCCESS;


inline static ht_index_t hash(const char *const key)
{
   return qhash(key, strlen(key));
}

HtHashtable* construct_hashtable(void)
{
    HtHashtable *restrict ht_hashTable = (HtHashtable *)malloc(sizeof(HtHashtable));
   
    if (ht_hashTable == NULL)
    {
        ht_result = HT_BAD_ALLOC;
        return NULL;
    }
   
    for (register ht_index_t i = 0;; i++)
    {
        if (list_construct(ht_hashTable->lists + i) == NULL)
        {
            destruct_hashtable(ht_hashTable);
            ht_result = HT_BAD_ALLOC;
            
            return NULL;
        }
    
        if (i == _HT_N_HASHTABLE_LISTS - 1)
        {
            ht_result = HT_SUCCESS;
            return ht_hashTable;
        }
    }
}

void destruct_hashtable(HtHashtable *restrict ht_hashtable)
{
    if (ht_hashtable == NULL)
        ht_result = HT_BAD_ARGUMENTS;
    else
    {
        for (register ht_index_t i = 0;; i++)
        {
            list_destruct(ht_hashtable->lists + i);
            
            if (i == _HT_N_HASHTABLE_LISTS - 1)
                break;
        }
        
        free(ht_hashtable);
        
        ht_result = HT_SUCCESS;
    }
}


HtValue* hashtable_insert(      HtHashtable *restrict ht_hashtable, const char *restrict key, const HtValue *restrict ht_value)
{
    if (ht_hashtable == NULL || key == NULL || ht_value == NULL)
    {
        ht_result = HT_BAD_ARGUMENTS;
        return NULL;
    }
    
    _HtList *restrict ht_list = ht_hashtable->lists + hash(key);
    
    if (list_find_value(ht_list, key) != NULL)
    {
        ht_result = HT_BAD_KEY;
        return NULL;
    }
    
    HtValue *restrict value_address = list_insert(ht_list, key, ht_value);
    
    if (value_address == NULL)
        ht_result = HT_BAD_ALLOC;
    else
        ht_result = HT_SUCCESS;
    
    return value_address;
}

HtValue* hashtable_remove(      HtHashtable *restrict ht_hashtable, const char *restrict key)
{
    if (ht_hashtable == NULL || key == NULL)
    {
        ht_result = HT_BAD_ARGUMENTS;
        return NULL;
    }
    
    HtValue *restrict value_address = list_remove(ht_hashtable->lists + hash(key), key);
    
    if (value_address == NULL)
        ht_result = HT_BAD_KEY;
    else
        ht_result = HT_SUCCESS;
    
    return value_address;
}

HtValue* hashtable_search(const HtHashtable *restrict ht_hashtable, const char *restrict key)
{
    if (ht_hashtable == NULL || key == NULL)
    {
        ht_result = HT_BAD_ARGUMENTS;
        return NULL;
    }
    
    HtValue *restrict value_address = list_find_value(ht_hashtable->lists + hash(key), key);

    if (value_address == NULL)
        ht_result = HT_BAD_KEY;
    else
        ht_result = HT_SUCCESS;
    
    return value_address;
}


HtResult verify_hashtable(const HtHashtable *restrict ht_hashtable)
{
    if (ht_hashtable == NULL)
        ht_result = HT_BAD_ARGUMENTS;
    else
        for (register ht_index_t i = 0;; i++)
        {
            if (verify_list(ht_hashtable->lists + i) == _HT_LIST_FAULT)
            {
                ht_result = HT_BAD_LIST;
                break;
            }
            
            if (i == _HT_N_HASHTABLE_LISTS - 1)
            {
                ht_result = HT_SUCCESS;
                break;
            }
        }
        
    return ht_result;
}


inline HtResult control_hashtable(void)
{
    return ht_result;
}