#include "input_ouput.h"

Trie read_dictionary(char* dict_file_path){
	Trie trie = trie_make();
	FILE *file = fopen(dict_file_path,"r");
	int len = 0;
	char buff[255];
	unsigned char ch;
	
	while(!feof(file)){
		if ((ch = getc(file)) != 10){
			buff[len] = ch;
			len++;
		} else {
			trie_insert(&trie, buff, len);
			len = 0;
		}
		
	}
	
	fclose(file);

	return trie;
}
