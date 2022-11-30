#include "input_ouput.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void read_dictionary(char* dict_file_path, Trie trie){
	FILE *file = fopen(dict_file_path,"r");
	int len = 0;
	char buff[255];
	unsigned char ch;
	
	while(!feof(file)){
		if ((ch = (unsigned char)getc(file)) != 10){
			buff[len] = ch;
			len++;
		} else {
			trie_insert(&trie, buff, len, 1);
			len = 0;
		}
	}
	fclose(file);
}

static inline void *id(void *data){
	return data;
}

static inline unsigned cache_hash(Cache cache) {
	return hash(cache->wrd);
} 

CHash read_cache(char* cache_file_path) {
	CHash hstb = chash_make(255, (CopyFunc) id,
															 (DestroyFunc) cache_destroy,
															 (CompareFunc) cache_compare,
															 (HashFunc) cache_hash);
	FILE *file = fopen(cache_file_path,"r");
	char buff_word[255];
	char buff_suggs[255];
	int amount;
	unsigned char ch;

	while (!feof(file)) {
		fscanf(file, "%[^,], %d", buff_word, &amount);
		fscanf(file, "%[^\n]\n", buff_suggs);
		Cache new_cache = cache_make(buff_word, buff_suggs, amount, 1);
		chash_insert(hstb, (void*) new_cache);	
	}
	return hstb;
}


void read_text(char* text_file_path, int func(char*, int, void*), void* data) {
	FILE *text = fopen(text_file_path, "r");
	int len = 0;
	char buff[255];
	unsigned char ch;

	while(!feof(text)) {
		ch = tolower((unsigned char)getc(text));
		if (97 <= ch && ch <= 123) {
			buff[len] = ch;
			len++;
		} else {
			if (len != 0) {
				func(buff, len, data);
				len = 0;
			}
		}
	}
	fclose(text);
}

