#include <stdio.h>
#include "include/hashtable.h"

/* X86_64
 * Improved performance
 * Memory damage
 * 32-byte strings only
 */


int main(void)
{
    HtHashtable *restrict ht_hashtable = construct_hashtable();
    
    hashtable_insert(ht_hashtable, "DUDE", &(HtValue){ .age = 30 });
    hashtable_insert(ht_hashtable, "LOL",  &(HtValue){ .age = 40 });
    hashtable_insert(ht_hashtable, "KEK",  &(HtValue){ .age = 50 });
    
    printf("%ld\n", hashtable_remove(ht_hashtable, "DUDE")->age);
    printf("%p\n", hashtable_search(ht_hashtable, "DUDE"));
    
    destruct_hashtable(ht_hashtable);
    
    return 0;
}
