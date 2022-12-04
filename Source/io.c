#include "input_ouput.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void assert_file(FILE* file){
	if (file == NULL){
		fprintf(stderr, "File openning fail,\n");
		exit(1);
	}
}

int get_text_word(FILE* text, char* buff, int *line) {
	char c;
	int len = 0;
	while((c = getc(text)) != EOF) {
		c = tolower(c);
		if (isalpha(c)) {
			buff[len] = c;
			len++;
		} else {
			if (len != 0) {
				buff[len] = '\0';
				len = 0;
			}
			if (c == 10) // 10 <=> '\n' 
				(*line)++;
		}
	}
	return len;
}

void read_dictionary(char* dictFilePath, Trie trie){
	FILE *dictFile = fopen(dictFilePath,"r");
	assert_file(dictFile);
	int len = 0;
	char buff[255];
	unsigned char ch;
	
	while(!feof(dictFile)){
		if ((ch = (unsigned char)getc(dictFile)) != 10){
			buff[len] = ch;
			len++;
		} else {
			trie_insert(&trie, buff, len, "d");
			len = 0;
		}
	}
	fclose(dictFile);
}

CHash read_cache(char* cacheFilePath, int table_size, Trie trie) {
	CHash hstb = cache_hstb_make(table_size);
	FILE *cacheFile = fopen(cacheFilePath,"r");
	assert_file(cacheFile);
	char buffWord[255];
	char buffSuggestions[MAX_SUGGESTIONS][255];
	int numSugg;
	unsigned char ch;

	while (!feof(cacheFile)) {
		fscanf(cacheFile, "%[^,], %d, ", buffWord, &numSugg);
		trie_insert(&trie, buffWord, strlen(buffWord), "c");
		for (int i = 0; i < numSugg - 1; i++)
			fscanf(cacheFile, "%[^,], ", buffSuggestions[i]);
		fscanf(cacheFile, "%[^\n]\n", buffSuggestions[numSugg - 1]);
		chash_insert(hstb, (void*) cache_make(buffWord, (char**)buffSuggestions, numSugg));
	}
	fclose(cacheFile);
	return hstb;
}

void print_text_suggestions(const char* suggestionFilePath, Cache cache, int line) {
	FILE *suggestions = fopen(suggestionFilePath, "a");
	assert_file(suggestions);
	char **suggs = cache->suggs;
	int numSugg = cache->n_suggs;

	fprintf(suggestions, "Line %d, \"%s\" not found in the dictionaty.\n", line, cache->wrd);
	fprintf(suggestions, "Maybe you meant: ");
	for (int i = 0; i < numSugg - 1; i++)
		fprintf(suggestions,"%s, ",suggs[i]);
	fprintf(suggestions, "%s.\n", suggs[numSugg - 1]);
	fclose(suggestions);

}

void print_cache_data(const char* cacheFilePath, Cache cache) {
	FILE *cacheFile = fopen(cacheFilePath, "a");
	assert_file(cacheFile);
	char **suggs = cache->suggs;
	int numSugg = cache->n_suggs;

	fprintf(cacheFile, "%s, %d, ", cache->wrd, numSugg);
	for (int i = 0; i < numSugg - 1; i++)
		fprintf(cacheFile,"%s, ",suggs[i]);
	fprintf(cacheFile, "%s.\n",suggs[numSugg - 1]);
	fclose(cacheFile);

}
