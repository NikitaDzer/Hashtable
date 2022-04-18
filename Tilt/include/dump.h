// Created by Nikita Dzer on 09.04.2022.

#define _CRT_SECURE_NO_WARNINGS

#ifndef HASHTABLE_DUMP_H
#define HASHTABLE_DUMP_H

#include "hashtable.h"



HtHashtable* _process_construct_hashtable(const char *restrict func, const long line, const char *restrict file);

void _process_destruct_hashtable(HtHashtable *restrict ht_hashtable,
                                 const char *restrict func, const long line, const char *restrict file);


HtValue* _process_hashtable_insert(HtHashtable *restrict ht_hashtable, const char *restrict key, const HtValue *restrict ht_value,
                                   const char *restrict func, const long line, const char *restrict file);

HtValue* _process_hashtable_remove(HtHashtable *restrict ht_hashtable, const char *restrict key,
                                   const char *restrict func, const long line, const char *restrict file);

HtValue* _process_hashtable_search(const HtHashtable *restrict ht_hashtable, const char *restrict key,
                                   const char *restrict func, const long line, const char *restrict file);

HtResult _process_verify_hashtable(const HtHashtable *restrict ht_hashtable,
                                   const char *restrict func, const long line, const char *restrict file);

#endif // HASHTABLE_DUMP_H
