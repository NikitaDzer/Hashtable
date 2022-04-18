#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include "include/hashtable.h"


int main(void)
{
    
    HtHashtable* restrict ht_hashtable = construct_hashtable();
    const char person[HT_MAX_N_KEY_CHARS] = "bro";

    hashtable_insert(ht_hashtable, person, &(HtValue){.age = 18 });

    HtValue *restrict bro = hashtable_search(ht_hashtable, transform_key("bro"));
    
    if (bro == NULL)
    {
        if (control_hashtable() == HT_BAD_KEY)
            printf("No bro in hashtable...");
    }
    else
    {
        printf("Bro age is %ld\n", bro->age);
        hashtable_remove(ht_hashtable, transform_key("bro"));
    }

    destruct_hashtable(ht_hashtable);

    return 0;
}