// Created by Nikita Dzer on 09.04.2022.

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <assert.h>
#include <stdbool.h>

#include "settings.h"
#include "htdef.h"
#include "list.h"

#ifndef HT_N_HASHTABLE_LISTS
#error Define HT_N_HASHTABLE_LISTS in file htdef.h
#endif

#define _HT_N_HASHTABLE_LISTS (HT_N_HASHTABLE_LISTS)

static_assert(   _HT_N_HASHTABLE_LISTS == (UCHAR_MAX + 1)
              || _HT_N_HASHTABLE_LISTS == (USHRT_MAX + 1)
              || _HT_N_HASHTABLE_LISTS == (UINT_MAX  + 1)
              || _HT_N_HASHTABLE_LISTS == (ULONG_MAX + 1),
              "Define HT_N_HASHTABLE_LISTS must be equal to UCHAR_MAX + 1 or USHRT_MAX + 1 or UINT_MAX + 1 or ULONG_MAX + 1.");

/*
 *
 * HtInstance
 * HtList
 * HtListItem
 * HtResult
 *
 * construct_hashtable()
 * destruct_hashtable()
 * hashtable_insert()
 * hashtable_search()
 * hashtable_remove()
 * hashtable_clear()
 * hashtable_has()
 *
 * control_hashtable();
 *
 */




typedef enum HtResult
{
    HT_SUCCESS   = 0 << 0,
    HT_BAD_ALLOC = 1 << 0,
} HtResult;


#define HT_MAX_N_CACHE_KEY_CHARS (HT_MAX_N_KEY_CHARS - sizeof(HtValue *))

typedef struct _HtCachePair
{
    _Alignas(HT_KEY_ALIGNMENT) char key[HT_MAX_N_CACHE_KEY_CHARS];
                              HtValue *restrict ht_value;
} _HtCachePair;

typedef struct HtHashtable
{
   _HtList lists[_HT_N_HASHTABLE_LISTS];
} HtHashtable;


HtHashtable* construct_hashtable(void);

void          destruct_hashtable(HtHashtable *restrict ht_hashtable);


HtValue* hashtable_insert(      HtHashtable *restrict ht_hashtable, const char *restrict key, const HtValue *restrict ht_value);

HtValue* hashtable_remove(      HtHashtable *restrict ht_hashtable, const char *restrict key);

HtValue* hashtable_search(const HtHashtable *restrict ht_hashtable, const char *restrict key);

HtValue* hashtable_clear (      HtHashtable *restrict ht_hashtable);


inline HtResult control_hashtable(void);

inline void     report_hashtable (void);
#endif // HASHTABLE_H
