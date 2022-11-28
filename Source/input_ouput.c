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

void read_cache(char* cache_file_path, CHash hstb) {
	FILE *file = fopen(cache_file_path,"r");
	char buff[255];
	int amount;
	unsigned char ch;

	while (!feof(file)) {
		Cache new_cache = malloc(sizeof(struct _Cache));
		fscanf(file, "%[^,], %d", buff, &amount);
		new_cache->wrd = malloc(sizeof(char) * (strlen(buff) + 1));	
		strcpy(new_cache->wrd, buff);
		new_cache->n_suggs = amount;
		fscanf(file, "%[^\n]\n", buff);
		new_cache->suggs = malloc(sizeof(char) * (strlen(buff) + 1));	
		strcpy(new_cache->suggs, buff);
		chash_insert(hstb, (void*) new_cache);	
	}
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
