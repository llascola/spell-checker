#ifndef __INPUT_OUPUT__
#define __INPUT_OUPUT__
#include <stdio.h>
#include "../Structures/Trie/trie.h"
#include "../Structures/Hash/hash_ch.h"
#include "../Structures/Cache/cache.h"
#include "utils.h"

void read_dictionary(char* dict_file_path, Trie trie);

CHash read_cache(char* cache_file_path); 

void read_text(char* text_file_path, int func(char*, int, int, void*), void* data);

#endif

