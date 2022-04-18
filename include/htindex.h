// Created by Nikita Dzer on 16.04.2022.

#ifndef HASHTABLE_HTINDEX_H
#define HASHTABLE_HTINDEX_H

#include "config.h"


#ifndef HT_HASHTABLE_SIZE
#error Define HT_HASHTABLE_SIZE in file htdef.h.
#endif


#if   HT_HASHTABLE_SIZE == HT_HASHTABLE_XS
typedef unsigned char  ht_index_t;
#elif HT_HASHTABLE_SIZE == HT_HASHTABLE_L
typedef unsigned short ht_index_t;
#elif HT_HASHTABLE_SIZE == HT_HASHTABLE_XXL
typedef unsigned int   ht_index_t;
#else 
#error HT_HASHTABLE_SIZE in file htdef.h must be HT_HASHTABLE_XS or HT_HASHTABLE_L or HT_HASHTABLE_XXL.
#endif // HT_HASHTABLE_SIZE

#endif // HASHTABLE_HTINDEX_H