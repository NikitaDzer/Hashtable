#include <stdio.h>
#include "include/hashTable.h"

/* X86_64
 * Improved performance
 * Memory damage
 * 32-byte strings only
 */

int main(void)
{   
   HashTable *const p_hashTable = construct_hashTable();
   
   hashTable_insert(p_hashTable, "dude", (ht_value_t){ .age = 10 });
   
   printf("%d\n", hashTable_search(p_hashTable, "dude")->age);
   
   hashTable_delete(p_hashTable, "dude");
   hashTable_insert(p_hashTable, "dude", (ht_value_t){ .age = 20 });
   hashTable_insert(p_hashTable, "dude", (ht_value_t){ .age = 30 });
   
   printf("%d\n", hashTable_search(p_hashTable, "dude")->age);
   
   destruct_hashTable(p_hashTable);
   
   printf("Hello, World!\n");
   return 0;
}
