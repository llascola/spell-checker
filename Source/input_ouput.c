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

CHash read_cache(char* cache_file_path, int table_size) {
	CHash hstb = cache_hstb_make(table_size);
	FILE *file = fopen(cache_file_path,"r");
	char buff_word[255];
	char buff_suggs[MAX_SUGGESTIONS][255];
	int n_suggs;
	unsigned char ch;

	while (!feof(file)) {
		fscanf(file, "%[^,], %d, ", buff_word, &n_suggs);
		for (int i = 0; i < n_suggs - 1; i++)
			fscanf(file, "%[^,], ", buff_suggs[i]);
		fscanf(file, "%[^\n]\n", buff_suggs[n_suggs - 1]);
		chash_insert(hstb, (void*) cache_make(buff_word, (char**)buff_suggs, n_suggs));
	}
	fclose(file);
	return hstb;
}


void read_text(char* text_file_path, int func(char*, int, int, void*), void* data) {
	FILE *text = fopen(text_file_path, "r");
	int len = 0;
	int line = 0;
	char buff[255];
	unsigned char ch;

	while(!feof(text)) {
		ch = tolower((unsigned char)getc(text));
		if (97 <= ch && ch <= 123) {
			buff[len] = ch;
			len++;
		} else {
			if (len != 0) {
				buff[len] = '\0';
				func(buff, len, line, data);
				len = 0;
			}
			if (ch == 10) // 10 <=> '\n' 
				line++;
		}
	}
	fclose(text);
}

//void print_text_suggestions(const char* suggestion_file_path, char* wrd)

