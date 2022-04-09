#include <stdio.h>
#include <stdlib.h>
#include "include/hashTable.h"
#include "include/dump.h"

/* X86_64
 * Improved performance
 * Memory damage
 * 32-byte strings only
 */

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

int main(void)
{   
	HashTable *const p_hashTable = construct_hashTable();
   
   
	long text_size = 0;
	const char* const text = get_text("../HarryPotter.txt", &text_size);
	
	char temp_buffer[N_KEY_CHARS] = "";

	for (long k = 0; k < 1; k++)
		for (long i = 0; i < text_size; i++)
		{
			if (text[i] == ' ' || text[i] == '\n')
				continue;

			i += put_word(temp_buffer, text + i);

			hashTable_insert(p_hashTable, temp_buffer, (ht_value_t) { .position = i });

			for (long j = i; j < text_size; j++)
				if (text[j] == ' ' || text[j] == '\n')
					break;

		}
  
	for (long k = 0; k < 1; k++)
		for (long i = 0; i < text_size; i++)
		{
			if (text[i] == ' ' || text[i] == '\n')
				continue;

			i += put_word(temp_buffer, text + i);

			hashTable_search(p_hashTable, temp_buffer);

			for (long j = i; j < text_size; j++)
				if (text[j] == ' ' || text[j] == '\n')
					break;

		}
  
	for (long k = 0; k < 1; k++)
		for (long i = 0; i < text_size; i++)
		{
			if (text[i] == ' ' || text[i] == '\n')
				continue;

			i += put_word(temp_buffer, text + i);

			hashTable_delete(p_hashTable, temp_buffer);

			for (long j = i; j < text_size; j++)
				if (text[j] == ' ' || text[j] == '\n')
					break;

		}

	destruct_hashTable(p_hashTable);
   
   return 0;
}
