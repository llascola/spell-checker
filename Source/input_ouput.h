#ifndef __INPUT_OUPUT__
#define __INPUT_OUPUT__
#include <stdio.h>
#include "../Structures/Trie/trie.h"
#include "../Structures/Hash/hash_ch.h"

struct _Cache {
	char *wrd;
	char *suggs;
	int n_suggs;
};

typedef struct _Cache* Cache;

void read_dictionary(char* dict_file_path, Trie trie);

void read_cache(char* cache_file_path, CHash hstb);

void read_text(char* text_file_path, int func(char*, int, void*), void* data);
#endif

