// Created by Nikita Dzer on 09.04.2022.

#define _CRT_SECURE_NO_WARNINGS

#ifndef HASHTABLE_HASH_H
#define HASHTABLE_HASH_H

#include "htindex.h"

typedef ht_index_t hash_t;

extern inline hash_t dhash(const char* const buffer);

#endif // HASHTABLE_HASH_H
