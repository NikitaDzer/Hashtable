#include <stdio.h>
#include <stdlib.h>
#include "include/hashtable.h"
#include "include/dump.h"

/* X86_64
 * Improved performance
 * Memory damage
 * 32-byte strings only
 */
 
/*
 *
 * HtInstance
 * HtList
 * HtListItem
 *
 * construct_hashtable()
 * destruct_hashtable()
 * hashtable_insert()
 * hashtable_search()
 * hashtable_remove()
 * hashtable_clear()
 * hashtable_has()
 *
 */

/*
static const char* get_text(const char* const file_path, long *const p_text_size)
{
	FILE* const file = fopen(file_path, "r");

	if (file == NULL)
		return NULL;

	fseek(file, 0l, SEEK_END);

	const long file_size = ftell(file);
	char* const text = (char*)calloc(file_size + 1, sizeof(char));

	if (text == NULL)
	{
		fclose(file);
		return NULL;
	}
	
	fseek(file, 0, SEEK_SET);
	fread(text, sizeof(char), file_size + 1, file);
	fclose(file);

	if (p_text_size != NULL)
		*p_text_size = file_size + 1;

	return text;
}

static long put_word(char buffer[N_KEY_CHARS], const char* const start)
{
	const char *iterator = start;
	long i = 0;

	while (*iterator != '\0' && (i < N_KEY_CHARS))
	{
		buffer[i++] = *iterator++;

		if (*iterator == ' ' || *iterator == '\n')
			break;
	}

	if (i != N_KEY_CHARS)
		buffer[i] = '\0';

	return i;
}
*/


int main(void)
{
    HtHashtable *restrict ht_hashtable = construct_hashtable();
    destruct_hashtable(ht_hashtable);
    
    return 0;
}
