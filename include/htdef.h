//
// Created by User on 09.04.2022.
//

#ifndef HASHTABLE_HTDEF_H
#define HASHTABLE_HTDEF_H

#include <stddef.h>

#define HT_N_HASHTABLE_LISTS USHRT_MAX + 1
#define HT_DUMP

typedef struct HtValue
{
    long age;
} HtValue;

#endif // HASHTABLE_HTDEF_H
