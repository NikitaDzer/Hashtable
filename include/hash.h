// Created by Nikita Dze on 09.04.2022.

#ifndef HASHTABLE_HASH_H
#define HASHTABLE_HASH_H

#include <stddef.h>

typedef unsigned short hash_t;

hash_t qhash(const void *const buffer, const size_t buffer_bytes);

#endif // HASHTABLE_HASH_H
