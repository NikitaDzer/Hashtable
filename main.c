#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "include/hashtable.h"

/* X86_64
 * Improved performance
 * Memory damage
 * 32-byte strings only
 */

/*
static long get_file_size(FILE *restrict file)
{
    const long current_position = ftell(file);
    long file_size = 0;
    
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, current_position, SEEK_SET);
    
    return file_size;
}

static char* get_content(FILE *restrict file, long *restrict content_size)
{
    *content_size = get_file_size(file) + 1;
    if (*content_size == 0)
        return NULL;
    
    char *restrict content = (char *)calloc(*content_size, sizeof(char));
    if (content == NULL)
        return NULL;
    
    fread(content, sizeof(char), *content_size - 1, file);
    
    return content;
}

static char* make_key(char *restrict start, char *restrict end)
{
    register char *restrict iterator = start;
    
    for (; iterator != end; iterator += 1)
    {
        if (!isalnum(*iterator))
            break;
    }
    
    *iterator = '\0';
    
    return iterator;
}

static char *restrict* get_keys(const char *restrict file_path, long *restrict n_keys)
{
    if (file_path == NULL)
        return NULL;
    
    FILE *restrict file = fopen(file_path, "r");
    if (file == NULL)
        return NULL;
    
    long content_size = 0;
    char *restrict content = get_content(file, &content_size);
    if (content == NULL)
        return NULL;
    
    fclose(file);
    
    long local_n_keys = 0;
    char *restrict *restrict keys = (char **)calloc(content_size / 2, sizeof(char *));
    if (keys == NULL)
    {
        free(content);
        return NULL;
    }
    
    for (register long i = 0; i < content_size; i++)
    {
        if (!isalnum(content[i]))
            continue;
    
        keys[local_n_keys++] = content + i;
        i = make_key(content + i, content + content_size) - content;
    }
    
    *n_keys = local_n_keys;
    return keys;
}
*/

int main(void)
{
    HtHashtable *restrict ht_hashtable = construct_hashtable();
    /*
    long n_keys = 0;
    char *restrict *restrict keys = get_keys("../HarryPotter.txt", &n_keys);
    if (keys != NULL)
    {
        for (register long i = 0; i < n_keys; i++)
            hashtable_insert(ht_hashtable, keys[i], &(HtValue){ .age = i });
    }
    
    FILE *restrict report = fopen("uchar_6.txt", "w");
    
    for (register long i = 0; i < _HT_N_HASHTABLE_LISTS; i++)
        fprintf(report, "%-5ld %lld\n", i, ht_hashtable->lists[i].size);
    
    fclose(report);
     */
    
    destruct_hashtable(ht_hashtable);
    
    return 0;
}
