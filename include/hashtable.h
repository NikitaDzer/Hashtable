// Created by Nikita Dzer on 09.04.2022.

#ifndef HASHTABLE_H
#define HASHTABLE_H

// ---------------------------------------------------  Includes  ------------------------------------------------------------
#include <assert.h>
#include <stdbool.h>
#include <limits.h>

#include "settings.h"
#include "htdef.h"
#include "list.h"
// --------------------------------------------------- /Includes  ------------------------------------------------------------


// ---------------------------------------------------  Hashtable size  ------------------------------------------------------------
#ifndef HT_N_HASHTABLE_LISTS
#error Define HT_N_HASHTABLE_LISTS in file htdef.h
#endif

#define _HT_N_HASHTABLE_LISTS (HT_N_HASHTABLE_LISTS)

static_assert(   _HT_N_HASHTABLE_LISTS == (UCHAR_MAX + 1)
              || _HT_N_HASHTABLE_LISTS == (USHRT_MAX + 1)
              || _HT_N_HASHTABLE_LISTS == (UINT_MAX  + 1)
              || _HT_N_HASHTABLE_LISTS == (ULONG_MAX + 1),
              "Define HT_N_HASHTABLE_LISTS must be equal to UCHAR_MAX + 1 or USHRT_MAX + 1 or UINT_MAX + 1 or ULONG_MAX + 1.");
// --------------------------------------------------- /Hashtable size  ------------------------------------------------------------


// ---------------------------------------------------  Struct, enum  ------------------------------------------------------------
typedef enum HtResult
{
    HT_SUCCESS       = 0,
    HT_BAD_KEY       = 1,
    HT_BAD_ALLOC     = 2,
    HT_BAD_ARGUMENTS = 3,
    HT_BAD_LIST      = 4,
} HtResult;


typedef struct HtHashtable
{
   _HtList lists[_HT_N_HASHTABLE_LISTS];
} HtHashtable;
// --------------------------------------------------- /Struct, enum  ------------------------------------------------------------


// ---------------------------------------------------  Functions  ------------------------------------------------------------
HtHashtable* construct_hashtable(void);

void          destruct_hashtable(HtHashtable *restrict ht_hashtable);


HtValue* hashtable_insert(      HtHashtable *restrict ht_hashtable, const char *restrict key, const HtValue *restrict ht_value);

HtValue* hashtable_remove(      HtHashtable *restrict ht_hashtable, const char *restrict key);

HtValue* hashtable_search(const HtHashtable *restrict ht_hashtable, const char *restrict key);


HtResult verify_hashtable(const HtHashtable *restrict ht_hashtable);

extern inline HtResult control_hashtable(void);
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
