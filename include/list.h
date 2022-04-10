// Created by Nikita Dzer on 08.04.2022.

#ifndef HASHTABLE_LIST_H
#define HASHTABLE_LIST_H

#include "settings.h"
#include "htdef.h"

typedef signed long long int _ht_list_index_t;

extern const _ht_list_index_t _HT_LIST_SUCCESS;
extern const _ht_list_index_t _HT_LIST_FAULT;

typedef struct _HtListPair
{
   _Alignas(HT_KEY_ALIGNMENT) char key[HT_MAX_N_KEY_CHARS];
                              HtValue value;
} _HtListPair;

typedef struct _HtListNode
{
    _Alignas(HT_KEY_ALIGNMENT)           _HtListPair      pair;
    _Alignas(_Alignof(_ht_list_index_t)) _ht_list_index_t next;
} _HtListNode;

typedef struct _HtList
{
    _HtListNode *restrict nodes;
    _ht_list_index_t      free;
    _ht_list_index_t      head;
    _ht_list_index_t      size;
} _HtList;


_HtList*    list_construct(_HtList *restrict ht_list);

inline void list_destruct(_HtList* restrict ht_list);


HtValue* list_insert    (      _HtList *restrict ht_list, const char *restrict key, const HtValue *restrict ht_value);

HtValue* list_remove    (      _HtList *restrict ht_list, const char *restrict key);

HtValue* list_find_value(const _HtList *restrict ht_list, const char *restrict key);

_ht_list_index_t verify_list(const _HtList *restrict ht_list);

#endif // HASHTABLE_LIST_H
