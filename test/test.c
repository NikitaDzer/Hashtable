#define _CRT_SECURE_NO_WARNINGS



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <nmmintrin.h>
#include <immintrin.h>

#include "../hashtable.h"
#include "test.h"



const clock_t HT_TEST_FAILED = -1;


/*
static void free_keys(const char* restrict* restrict keys, const long n_keys, const HtTestType test_type)
{
    switch (test_type)
    {
    case HT_TEST_REGULAR:
    case HT_TEST_EXPANDED:
    {
        for (long i = 0; i < n_keys; i++)
            free(keys[i]);

        break;
    }

    case HT_TEST_ALIGNED:
    {
        for (long i = 0; i < n_keys; i++)
            _aligned_free(keys[i]);
        ;
        break;
    }

    default:
    {
        break;
    }
    }

    free(keys);
}

static long get_file_size(FILE* restrict file)
{
    const long current_position = ftell(file);
    long file_size = 0;

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, current_position, SEEK_SET);

    return file_size;
}

static char* get_content(FILE* restrict file, long* restrict content_size)
{
    *content_size = get_file_size(file) + 1;
    if (*content_size == 0)
        return NULL;

    char* restrict content = (char*)calloc(*content_size, sizeof(char));
    if (content == NULL)
        return NULL;

    fread(content, sizeof(char), *content_size - 1, file);

    return content;
}

static long make_key(char* restrict start, char* restrict end, char* restrict* restrict temp_key)
{
    register char* restrict iterator = start;

    for (; iterator != end; iterator += 1)
    {
        if (!isalnum((unsigned char)*iterator))
            break;
    }

    *iterator = '\0';
    *temp_key = _strdup(start);

    return iterator - start;
}

static char* expand_key(char* restrict key)
{
    _Alignas(HT_KEY_ALIGNMENT) char temp[HT_MAX_N_KEY_CHARS] = "";

    char* restrict expanded_key = (char*)malloc(HT_MAX_N_KEY_CHARS * sizeof(unsigned char));

    if (expanded_key == NULL)
        return NULL;

    strncpy(expanded_key, key, HT_MAX_N_KEY_CHARS);

    return expanded_key;
}

static char* align_key(char* restrict key)
{
    char* restrict aligned_key = (char*)_aligned_malloc(HT_MAX_N_KEY_CHARS * sizeof(unsigned char), HT_KEY_ALIGNMENT);

    if (aligned_key == NULL)
        return NULL;

    return strncpy(aligned_key, key, HT_MAX_N_KEY_CHARS);
}

static char* restrict* get_keys(const char* restrict file_path, long* restrict n_keys, const HtTestType test_type)
{
    if (file_path == NULL)
        return NULL;

    FILE* restrict file = fopen(file_path, "r");

    if (file == NULL)
        return NULL;

    long content_size = 0;
    char* restrict content = get_content(file, &content_size);

    if (content == NULL)
        return NULL;

    fclose(file);

    long local_n_keys = 0;
    char* restrict* restrict keys = (char**)calloc(content_size / 2, sizeof(char*));

    if (keys == NULL)
    {
        free(content);
        return NULL;
    }

    char* restrict temp_key = NULL;

    for (register long i = 0; i < content_size; i++)
    {
        if (!isalnum((unsigned char)content[i]))
            continue;

        i += make_key(content + i, content + content_size, &temp_key);

        if (temp_key == NULL)
            goto GetKeysFailure;

        switch (test_type)
        {
        case HT_TEST_REGULAR:
        {
            keys[local_n_keys] = _strdup(temp_key);

            if (keys[local_n_keys] == NULL)
                goto GetKeysFailure;

            local_n_keys += 1;

            break;
        }

        case HT_TEST_EXPANDED:
        {
            keys[local_n_keys] = expand_key(temp_key);

            if (keys[local_n_keys] == NULL)
                goto GetKeysFailure;

            local_n_keys += 1;

            break;
        }

        case HT_TEST_ALIGNED:
        {
            keys[local_n_keys] = align_key(temp_key);

            if (keys[local_n_keys] == NULL)
                goto GetKeysFailure;

            local_n_keys += 1;

            break;
        }

        default:
        {
            break;
        }
        }

        free(temp_key);
    }

    free(content);

    *n_keys = local_n_keys;
    return keys;

GetKeysFailure:
    if (temp_key != NULL)
        free(temp_key);

    free(content);
    free_keys(keys, local_n_keys, test_type);

    return NULL;
}

static clock_t bench_construct(HtHashtable* restrict* restrict ht_hashtable)
{
    const clock_t start = clock();

    HtHashtable* restrict temp_ht_hashtable = construct_hashtable();

    const clock_t duration = clock() - start;

    if (temp_ht_hashtable == NULL)
        return HT_TEST_FAILED;

    *ht_hashtable = temp_ht_hashtable;

    return duration;
}

static clock_t bench_destruct(HtHashtable* restrict ht_hashtable)
{
    const clock_t start = clock();

    destruct_hashtable(ht_hashtable);

    return clock() - start;
}

static clock_t bench_insert(HtHashtable* restrict ht_hashtable, const char* restrict key, const HtValue* restrict ht_value, const HtTestType test_type)
{
    clock_t duration = 0;

    switch (test_type)
    {
    case HT_TEST_REGULAR:
    {
        const clock_t start = clock();

        hashtable_insert(ht_hashtable, transform_key(key), ht_value);

        duration = clock() - start;

        break;
    }

    case HT_TEST_EXPANDED:
    case HT_TEST_ALIGNED:
    {
        const clock_t start = clock();

        hashtable_insert(ht_hashtable, key, ht_value);

        duration = clock() - start;

        break;
    }

    default:
    {
        break;
    }
    }

    if (control_hashtable() == HT_BAD_ALLOC)
        return HT_TEST_FAILED;

    return duration;
}

static clock_t bench_remove(HtHashtable* restrict ht_hashtable, const char* restrict key, const HtTestType test_type)
{
    clock_t duration = 0;

    switch (test_type)
    {
    case HT_TEST_REGULAR:
    {
        const clock_t start = clock();

        hashtable_remove(ht_hashtable, transform_key(key));

        duration = clock() - start;

        break;
    }

    case HT_TEST_EXPANDED:
    case HT_TEST_ALIGNED:
    {
        const clock_t start = clock();

        hashtable_remove(ht_hashtable, key);

        duration = clock() - start;

        break;
    }

    default:
    {
        break;
    }
    }

    return duration;
}

static clock_t bench_search(const HtHashtable* restrict ht_hashtable, const char* restrict key, const HtTestType test_type)
{
    clock_t duration = 0;

    switch (test_type)
    {
    case HT_TEST_REGULAR:
    {
        const clock_t start = clock();

        hashtable_search(ht_hashtable, transform_key(key));

        duration = clock() - start;

        break;
    }

    case HT_TEST_EXPANDED:
    case HT_TEST_ALIGNED:
    {
        const clock_t start = clock();

        hashtable_search(ht_hashtable, key);

        duration = clock() - start;

        break;
    }

    default:
    {
        break;
    }
    }

    return duration;
}


clock_t bench_hashtable_lib(const char* restrict file_path, const HtTestType test_type)
{
    if (file_path == NULL)
        return HT_TEST_FAILED;

    const long n_keys = 0;
    const char* restrict* restrict keys = get_keys(file_path, &n_keys, test_type);

    if (keys == NULL)
        return HT_TEST_FAILED;

    clock_t duration = 0;
    clock_t temp_duration = 0;
    HtHashtable* restrict ht_hashtable = NULL;

    duration = bench_construct(&ht_hashtable);

    if (duration == HT_TEST_FAILED)
    {
        free_keys(keys, n_keys, test_type);
        return HT_TEST_FAILED;
    }

    for (register long i = 0; i < n_keys; i++)
    {
        temp_duration = bench_insert(ht_hashtable, keys[i], &(HtValue){.age = i }, test_type);

        if (temp_duration == HT_TEST_FAILED)
        {
            free_keys(keys, n_keys, test_type);
            return HT_TEST_FAILED;
        }

        duration += temp_duration;
    }

    for (register long i = 0; i < n_keys; i++)
        duration += bench_search(ht_hashtable, keys[i], test_type);

    for (register long i = 0; i < n_keys; i++)
        duration += bench_remove(ht_hashtable, keys[i], test_type);

    duration += bench_destruct(ht_hashtable);

    free_keys(keys, n_keys, test_type);

    return duration;
}
*/


static void free_keys(const char* restrict* restrict keys, const long n_keys, const HtTestType test_type)
{
    switch (test_type)
    {
    case HT_TEST_REGULAR:
    case HT_TEST_EXPANDED:
    {
        for (long i = 0; i < n_keys; i++)
            free(keys[i]);

        break;
    }

    case HT_TEST_ALIGNED:
    {
        for (long i = 0; i < n_keys; i++)
            _aligned_free(keys[i]);
        ;
        break;
    }

    default:
    {
        break;
    }
    }

    free(keys);
}

static long get_file_size(FILE* restrict file)
{
    const long current_position = ftell(file);
    long file_size = 0;

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, current_position, SEEK_SET);

    return file_size;
}

static char* get_content(FILE* restrict file, long* restrict content_size)
{
    *content_size = get_file_size(file) + 1;
    if (*content_size == 0)
        return NULL;

    char* restrict content = (char*)calloc(*content_size, sizeof(char));
    if (content == NULL)
        return NULL;

    fread(content, sizeof(char), *content_size - 1, file);

    return content;
}

static long make_key(char* restrict start, char* restrict end)
{
    register char* restrict iterator = start;

    for (; iterator != end; iterator += 1)
    {
        if (!isalnum((unsigned char)*iterator))
            break;
    }

    *iterator = '\0';

    return iterator - start;
}

static char* expand_key(char* restrict key)
{
    char* restrict expanded_key = (char*)malloc(HT_MAX_N_KEY_CHARS * sizeof(unsigned char));

    if (expanded_key == NULL)
        return NULL;

    return strncpy(expanded_key, key, HT_MAX_N_KEY_CHARS);;
}

static char* align_key(char* restrict key)
{
    char* restrict aligned_key = (char*)_aligned_malloc(HT_MAX_N_KEY_CHARS * sizeof(unsigned char), HT_KEY_ALIGNMENT);

    if (aligned_key == NULL)
        return NULL;

    return strncpy(aligned_key, key, HT_MAX_N_KEY_CHARS);
}

static char* restrict* get_keys(const char* restrict file_path, long* restrict n_keys, const HtTestType test_type)
{
    if (file_path == NULL)
        return NULL;

    FILE* restrict file = fopen(file_path, "r");

    if (file == NULL)
        return NULL;

    long content_size = 0;
    char* restrict content = get_content(file, &content_size);

    if (content == NULL)
        return NULL;

    fclose(file);

    long local_n_keys = 0;
    char* restrict* restrict keys = (char**)calloc(content_size / 2, sizeof(char*));

    if (keys == NULL)
    {
        free(content);
        return NULL;
    }

    char* restrict temp_key = NULL;

    for (register long i = 0; i < content_size; i++)
    {
        if (!isalnum((unsigned char)content[i]))
            continue;

        temp_key = content + i;
        i += make_key(content + i, content + content_size);

        switch (test_type)
        {
            case HT_TEST_REGULAR:
            {
                keys[local_n_keys] = _strdup(temp_key);

                if (keys[local_n_keys] == NULL)
                    goto GetKeysFailure;

                local_n_keys += 1;

                break;
            }

            case HT_TEST_EXPANDED:
            {
                keys[local_n_keys] = expand_key(temp_key);

                if (keys[local_n_keys] == NULL)
                    goto GetKeysFailure;

                local_n_keys += 1;

                break;
            }

            case HT_TEST_ALIGNED:
            {
                keys[local_n_keys] = align_key(temp_key);

                if (keys[local_n_keys] == NULL)
                    goto GetKeysFailure;

                local_n_keys += 1;

                break;
            }

            default:
            {
                break;
            }
        }
    }

    free(content);

    *n_keys = local_n_keys;
    return keys;

GetKeysFailure:
    free(content);
    free_keys(keys, local_n_keys, test_type);

    return NULL;
}

static clock_t bench_methods(const char* restrict* restrict keys, const long n_keys, const int times, const HtTestType test_type)
{
    const clock_t start = clock();

    for (register int i = 0; i < times; i++)
    {
        HtHashtable* restrict ht_hashtable = construct_hashtable();

        switch (test_type)
        {
            case HT_TEST_REGULAR:
            {
                for (register long i = 0; i < n_keys; i++)
                    hashtable_insert(ht_hashtable, transform_key(keys[i]), &(HtValue){.age = i });

                for (register long i = 0; i < n_keys; i++)
                    hashtable_search(ht_hashtable, transform_key(keys[i]));

                for (register long i = 0; i < n_keys; i++)
                    hashtable_remove(ht_hashtable, transform_key(keys[i]));

                break;
            }

            case HT_TEST_EXPANDED:
            case HT_TEST_ALIGNED:
            {
                for (register long i = 0; i < n_keys; i++)
                    hashtable_insert(ht_hashtable, keys[i], &(HtValue){.age = i });

                for (register long i = 0; i < n_keys; i++)
                    hashtable_search(ht_hashtable, keys[i]);

                for (register long i = 0; i < n_keys; i++)
                    hashtable_remove(ht_hashtable, keys[i]);

                break;
            }

            default:
            {
                break;
            }       
        }

        destruct_hashtable(ht_hashtable);
    }

    return clock() - start;
}


clock_t bench_hashtable_lib(const char* restrict file_path, const int times, const HtTestType test_type)
{
    if (file_path == NULL || times <= 0)
        return HT_TEST_FAILED;

    const long n_keys = 0;
    const char* restrict* restrict keys = get_keys(file_path, &n_keys, test_type);

    if (keys == NULL)
        return HT_TEST_FAILED;

    const clock_t duration = bench_methods(keys, n_keys, times, test_type);

    free_keys(keys, n_keys, test_type);

    return duration;
}