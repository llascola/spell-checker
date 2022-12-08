#ifndef __INPUT_OUPUT__
#define __INPUT_OUPUT__
#include <stdio.h>
#include "../Structures/Trie/trie.h"
#include "tables.h"

int get_text_word(FILE* text, char* buff, int *line); 

void read_dictionary(char* dictFilePath, Trie trie);

CHash read_cache(char* cacheFilePath, int size_table, Trie trie);

void print_text_suggestions(const char* suggestionFilePath, Cache cache, int line);

void print_cache_data(const char* cacheFilePath, Cache cache);

#endif

