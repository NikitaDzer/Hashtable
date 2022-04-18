// Created by Nikita Dzer on 18.04.2022.

#include <limits.h>
#include <string.h>
#include "../include/hash.h"

extern inline hash_t dhash(const char* restrict key)
{
    /*
    register hash_t hash = key[0];
    register unsigned char i = 1;

    do
    {
        hash = ((hash >> 1) | (hash << (sizeof(hash_t) * CHAR_BIT - 1))) ^ key[i];
    } while (++i < 8);

    if (key[i] != '\0')
    {
        do
        {
            hash = ((hash >> 1) | (hash << (sizeof(hash_t) * CHAR_BIT - 1))) ^ key[i];
        } while (++i < 16);

        if (key[i] != '\0')
        {
            do
            {
                hash = ((hash >> 1) | (hash << (sizeof(hash_t) * CHAR_BIT - 1))) ^ key[i];
            } while (++i < 32);
        }
    }
    */

    register hash_t hash = key[0];
    register size_t len = strlen(key);

    for (register size_t i = 1; i < len; i++)
        hash = ((hash >> 1) | (hash << (sizeof(hash_t) * CHAR_BIT - 1))) ^ key[i];

    return hash;
}
