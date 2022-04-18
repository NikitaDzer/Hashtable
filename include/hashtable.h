// Created by Nikita Dzer on 09.04.2022.

#define _CRT_SECURE_NO_WARNINGS


#ifndef HASHTABLE_H
#define HASHTABLE_H

// ---------------------------------------------------  Includes  ------------------------------------------------------------
#include <stdbool.h>
#include <limits.h>

#include "config.h"
#include "list.h"
// --------------------------------------------------- /Includes  ------------------------------------------------------------




// ---------------------------------------------------  Struct, enum  ------------------------------------------------------------
typedef enum HtResult
{
    HT_SUCCESS = 0,
    HT_BAD_KEY = 1,
    HT_BAD_ALLOC = 2,
    HT_BAD_ARGUMENTS = 3,
    HT_BAD_LIST = 4,
} HtResult;


typedef struct HtHashtable
{
    _HtList lists[HT_HASHTABLE_SIZE];
} HtHashtable;
// --------------------------------------------------- /Struct, enum  ------------------------------------------------------------




// ---------------------------------------------------  Functions  ------------------------------------------------------------
HtHashtable* construct_hashtable(void);

void          destruct_hashtable(HtHashtable* restrict ht_hashtable);


HtValue* hashtable_insert(HtHashtable* restrict ht_hashtable, const char* restrict key, const HtValue* restrict ht_value);

HtValue* hashtable_remove(HtHashtable* restrict ht_hashtable, const char* restrict key);

HtValue* hashtable_search(const HtHashtable* restrict ht_hashtable, const char* restrict key);


HtResult verify_hashtable(const HtHashtable* restrict ht_hashtable);

extern inline HtResult control_hashtable(void);

extern inline const char* transform_key(const char* restrict key);
// --------------------------------------------------- /Functions  ------------------------------------------------------------




// ---------------------------------------------------  Proxied functions  ------------------------------------------------------------
#ifdef HT_DUMP
#include "dump.h"

#define construct_hashtable(void)                                                             \
       _process_construct_hashtable(__func__, __LINE__, __FILE__)

#define destruct_hashtable(ht_hashtable)                                                      \
        _process_destruct_hashtable(ht_hashtable, __func__, __LINE__, __FILE__)

#define hashtable_insert(ht_hashtable, key, ht_value)                                         \
        _process_hashtable_insert(ht_hashtable, key, ht_value, __func__, __LINE__, __FILE__)

#define hashtable_remove(ht_hashtable, key)                                                   \
        _process_hashtable_remove(ht_hashtable, key, __func__, __LINE__, __FILE__)

#define hashtable_search(ht_hashtable, key)                                                   \
        _process_hashtable_search(ht_hashtable, key, __func__, __LINE__, __FILE__)

#define verify_hashtable(ht_hashtable)                                                        \
        _process_verify_hashtable(ht_hashtable, __func__, __LINE__, __FILE__)
#endif // HT_DUMP
// --------------------------------------------------- /Proxied functions  ------------------------------------------------------------
#endif // HASHTABLE_H
