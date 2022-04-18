// Created by Nikita Dzer on 18.04.2022.

#define _CRT_SECURE_NO_WARNINGS

#ifndef HASHTABLE_DUMP_H
#define HASHTABLE_DUMP_H

#include <time.h>

typedef enum HtTestType
{
	HT_TEST_REGULAR  = 1,
	HT_TEST_EXPANDED = 2,
	HT_TEST_ALIGNED  = 3,
} HtTestType;

extern const clock_t HT_TEST_FAILED;

clock_t bench_hashtable_lib(const char* restrict file_path, const int times, const HtTestType test_type);


#endif // HASHTABLE_DUMP_H
