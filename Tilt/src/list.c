// Created by Nikita Dzer on 08.04.2022.

#define _CRT_SECURE_NO_WARNINGS



#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <nmmintrin.h>
#include <immintrin.h>

#include "../include/list.h"



typedef _ht_list_index_t index_t;



// ---------------------------------------------------  Constants  ------------------------------------------------------------
const index_t _HT_LIST_SUCCESS = 0;
const index_t _HT_LIST_FAULT = -1;
// --------------------------------------------------- /Constants  ------------------------------------------------------------



// ---------------------------------------------------  Static constants  ------------------------------------------------------------
static const index_t LIST_NO_FREE = -1;

static const index_t N_INITIAL_LIST_NODES = 16;
static const index_t LIST_NODES_MULTIPLIER = 2;
// --------------------------------------------------- /Static constants  ------------------------------------------------------------



/* --------------------------------------------------- Import function ------------------------------------------------------------ */
extern inline void StoreKey(__m256i* const restrict node_key, const __m256i* const restrict key);



// ---------------------------------------------------  Static functions  ------------------------------------------------------------
static inline void fill_free(_HtListNode* restrict nodes, const index_t list_size)
{
    const index_t last_index = list_size * LIST_NODES_MULTIPLIER - 1;

    for (register index_t i = list_size; i < last_index; i++)
        nodes[i].next = i + 1;

    nodes[last_index].next = LIST_NO_FREE;
}

static index_t get_free(_HtList* restrict ht_list)
{
    if (ht_list->free != LIST_NO_FREE)
        return ht_list->free;

    const index_t size = ht_list->size;
    const index_t capacity = size * LIST_NODES_MULTIPLIER;

    ht_list->nodes = (_HtListNode*)_aligned_realloc(ht_list->nodes, capacity * sizeof(_HtListNode), _Alignof(_HtListNode));
    if (ht_list->nodes == NULL)
        return _HT_LIST_FAULT;

    fill_free(ht_list->nodes, size);

    ht_list->free = size;

    return size;
}

static inline bool is_in_range(const index_t index)
{
    return 0 <= index || index == LIST_NO_FREE;
}
// --------------------------------------------------- /Static functions  ------------------------------------------------------------



// ---------------------------------------------------  Export functions  ------------------------------------------------------------
_HtList* list_construct(_HtList* restrict ht_list)
{
    ht_list->nodes = (_HtListNode*)_aligned_malloc(N_INITIAL_LIST_NODES * sizeof(_HtListNode), _Alignof(_HtListNode));

    if (ht_list->nodes == NULL)
        return NULL;

    ht_list->free = 0;
    ht_list->head = LIST_NO_FREE;
    ht_list->size = 0;

    for (register index_t i = 0; i < N_INITIAL_LIST_NODES - 1; i++)
        ht_list->nodes[i].next = i + 1;

    ht_list->nodes[N_INITIAL_LIST_NODES - 1].next = LIST_NO_FREE;

    return ht_list;
}

extern inline void list_destruct(_HtList* restrict ht_list)
{
    if (ht_list->nodes != NULL)
        _aligned_free(ht_list->nodes);
}


HtValue* list_insert(_HtList* restrict ht_list, const char* restrict key, const HtValue* restrict ht_value)
{
    const index_t free = get_free(ht_list);

    if (free == _HT_LIST_FAULT)
        return NULL;

    _HtListNode* restrict nodes = ht_list->nodes;
    const _ht_list_index_t nextFree = nodes[free].next;

    /* GCC style inline asm
    __asm__ __volatile__(
        "vlddqu  (%1,1), %%ymm0\n"
        "vmovdqa %%ymm0, (%0,1)\n"
        :
    :   "r" (nodes[free].pair.key), "r" (key)
        : "%ymm0"
        );
     */
    // _mm256_store_si256((__m256i*)nodes[free].pair.key, _mm256_load_si256((const __m256i*)key));
    StoreKey((__m256i*)nodes[free].pair.key, (const __m256i*)key);
 
    nodes[free].pair.value = *ht_value;
    nodes[free].next = ht_list->head;

    ht_list->free = nextFree;
    ht_list->head = free;
    ht_list->size += 1;

    return &nodes[free].pair.value;
}

HtValue* list_remove(_HtList* restrict ht_list, const char* restrict key)
{
    _HtListNode* restrict nodes = ht_list->nodes;

    register index_t index = LIST_NO_FREE;
    register index_t prev = LIST_NO_FREE;

    const __m256i KEY = _mm256_load_si256(key);

    for (register index_t i = ht_list->head; i != LIST_NO_FREE; prev = i, i = nodes[i].next)
        if (_mm256_movemask_epi8(_mm256_cmpeq_epi64(_mm256_load_si256(nodes[i].pair.key), KEY)) == -1)
        {
            index = i;
            break;
        }

    if (index == LIST_NO_FREE)
        return NULL;

    if (ht_list->head == index)
        ht_list->head = nodes[index].next;
    else
        nodes[prev].next = nodes[index].next;

    nodes[index].next = ht_list->free;

    ht_list->free = index;
    ht_list->size -= 1;

    return &nodes[index].pair.value;
}

HtValue* list_find_value(const _HtList* restrict ht_list, const char* restrict key)
{
    register _HtListNode* restrict nodes = ht_list->nodes;

    const __m256i KEY = _mm256_load_si256(key);

    for (register index_t i = ht_list->head; i != LIST_NO_FREE; i = nodes[i].next)
        if (_mm256_movemask_epi8(_mm256_cmpeq_epi64(_mm256_load_si256(nodes[i].pair.key), KEY)) == -1)
            return &nodes[i].pair.value;

    return NULL;
}

index_t   verify_list(const _HtList* restrict ht_list)
{
    if (ht_list->nodes == NULL)
        return _HT_LIST_FAULT;

    if (!is_in_range(ht_list->free))
        return _HT_LIST_FAULT;

    if (!is_in_range(ht_list->head))
        return _HT_LIST_FAULT;

    if (!is_in_range(ht_list->size))
        return _HT_LIST_FAULT;

    return _HT_LIST_SUCCESS;
}
// --------------------------------------------------- /Export functions  ------------------------------------------------------------