// Created by Nikita Dzer on 09.04.2022.

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <nmmintrin.h>
#include <immintrin.h>
#include <intrin.h>

#include "../include/hashtable.h"
#include "../include/hash.h"
#include "../include/htindex.h"




#undef construct_hashtable
#undef destruct_hashtable
#undef hashtable_insert
#undef hashtable_remove
#undef hashtable_search
#undef verify_hashtable



HtResult ht_result = HT_SUCCESS;




HtHashtable* construct_hashtable(void)
{
    HtHashtable* restrict ht_hashTable = (HtHashtable*)_aligned_malloc(sizeof(HtHashtable), 32);
    // sizeof(_HtList) == 32, but it is supported only on X86_64

    if (ht_hashTable == NULL)
    {
        ht_result = HT_BAD_ALLOC;
        return NULL;
    }

    memset(ht_hashTable->lists, 0, sizeof(_HtList) * HT_HASHTABLE_SIZE);

    for (register ht_index_t i = 0;; i++)
    {
        if (list_construct(ht_hashTable->lists + i) == NULL)
        {
            destruct_hashtable(ht_hashTable);
            ht_result = HT_BAD_ALLOC;

            return NULL;
        }

        if (i == HT_HASHTABLE_SIZE - 1)
        {
            ht_result = HT_SUCCESS;
            return ht_hashTable;
        }
    }
}

void destruct_hashtable(HtHashtable* restrict ht_hashtable)
{
    if (ht_hashtable == NULL)
        ht_result = HT_BAD_ARGUMENTS;
    else
    {
        for (register ht_index_t i = 0;; i++)
        {
            list_destruct(ht_hashtable->lists + i);

            if (i == HT_HASHTABLE_SIZE - 1)
                break;
        }

        _aligned_free(ht_hashtable);

        ht_result = HT_SUCCESS;
    }
}


HtValue* hashtable_insert(HtHashtable* restrict ht_hashtable, const char* restrict key, const HtValue* restrict ht_value)
{
    if (ht_hashtable == NULL || key == NULL || ht_value == NULL)
    {
        ht_result = HT_BAD_ARGUMENTS;
        return NULL;
    }

    _HtList* restrict ht_list = ht_hashtable->lists + dhash(key);

    if (list_find_value(ht_list, key) != NULL)
    {
        ht_result = HT_BAD_KEY;
        return NULL;
    }

    HtValue* restrict value_address = list_insert(ht_list, key, ht_value);

    if (value_address == NULL)
        ht_result = HT_BAD_ALLOC;
    else
        ht_result = HT_SUCCESS;

    return value_address;
}

HtValue* hashtable_remove(HtHashtable* restrict ht_hashtable, const char* restrict key)
{
    if (ht_hashtable == NULL || key == NULL)
    {
        ht_result = HT_BAD_ARGUMENTS;
        return NULL;
    }

    HtValue* restrict value_address = list_remove(ht_hashtable->lists + dhash(key), key);

    if (value_address == NULL)
        ht_result = HT_BAD_KEY;
    else
        ht_result = HT_SUCCESS;

    return value_address;
}

HtValue* hashtable_search(const HtHashtable* restrict ht_hashtable, const char* restrict key)
{
    if (ht_hashtable == NULL || key == NULL)
    {
        ht_result = HT_BAD_ARGUMENTS;
        return NULL;
    }

    HtValue* restrict value_address = list_find_value(ht_hashtable->lists + dhash(key), key);

    if (value_address == NULL)
        ht_result = HT_BAD_KEY;
    else
        ht_result = HT_SUCCESS;

    return value_address;
}


HtResult verify_hashtable(const HtHashtable* restrict ht_hashtable)
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

            if (i == HT_HASHTABLE_SIZE - 1)
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

inline const char* transform_key(const char* restrict key)
{
    _Alignas(HT_MAX_N_KEY_CHARS) static char transformed_key[HT_MAX_N_KEY_CHARS];

    strncpy(transformed_key, key, HT_MAX_N_KEY_CHARS);

    return transformed_key;
}