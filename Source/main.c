#include <stdio.h>
#include <assert.h>
#include "io.h"
#include "corrector.h"
#include <stdlib.h>
#include <string.h>

void print_cache_custom(Cache cach){
	printf("%s-----\n",cach->wrd);
}

void print_word_custom(Word word){
	printf("%s-----\n",word->word);
}
void printf_string(char* w){
	printf("%s\n", w);
}

void* string_copy(char* w){
	int len = strlen(w);
	char* copy = malloc(sizeof(char) * (len + 1));
	strcpy(copy, w);
	return copy;
}
int test0(){
	CHash strings = chash_make(2,(CopyFunc) string_copy, free,(CompareFunc) strcmp,(HashFunc) hash);
	chash_insert(strings, "Hola");
	chash_insert(strings, "ola");
	chash_insert(strings, "Hol");
	chash_insert(strings, "Hoxxxla");
	chash_visit(strings,(VisitorFunc) printf_string);
	chash_delete(strings, "Hola");
	chash_visit(strings,(VisitorFunc) printf_string);
	chash_destroy(strings);
	return 0; 
}


int test1(){
	CHash table = cache_hstb_make(2);	

	Cache cache1 = cache_make("ola", 3);
	Cache cache2 = cache_make("Hla", 3);
	Cache cache3 = cache_make("Hoa", 3);
	cache_add_sugg(cache1, "perro", 5);	
	cache_add_sugg(cache1, "gato", 4);	
	cache_add_sugg(cache1, "zorrino", 7);	
	cache_add_sugg(cache2, "zorrino", 7);	
	chash_insert(table, cache1);
	chash_insert(table, cache2);
	chash_insert(table, cache3);
	chash_visit(table, (VisitorFunc)&print_cache_custom);
	printf("Hola mundo\n");
	chash_delete(table, cache3);
	chash_visit(table, (VisitorFunc)&print_cache_custom);
	printf("Hola mundo\n");

	chash_destroy(table);
	return 0;
}

int test2(){
	CHash table = word_hstb_make();
	Word word1 = word_make("Hola", 4);
	Word word2 = word_make("Hla", 3);
	Word word3 = word_make("Hoa", 3);
	Word word4 = word_make("Hol", 3);
	chash_insert(table, word1);
	chash_insert(table, word2);
	chash_insert(table, word3);
	chash_insert(table, word4);
	chash_visit(table, (VisitorFunc) print_word_custom);
	printf("Hola mundo\n");
	chash_delete(table, word2);
	chash_delete(table, word4);
	chash_visit(table, (VisitorFunc) print_word_custom);
	printf("Hola mundo\n");
	chash_visit(table, (VisitorFunc) print_word_custom);
	printf("Hola mundo\n");
	chash_destroy(table);
	return 0;
}

/*
int main(){
	test0();
	//test1();
	//test2();
	return 0;
}
*/


int main(int argc, char* argv[]) {
	assert(argc == 3);

	char buff[255];
	char cacheFilePath[255];

	int line = 0;
	int len;
	int flag;

	char status;
	
	Cache cache = NULL;
	struct _Cache cacheSearch;

	Trie trie = trie_make();	
	CHash cacheHstb = NULL;

	printf("Insert dictionary's file path: ");
	scanf("%s", buff);
	read_dictionary(buff, trie);

	printf("Insert cache's file path: ");
	scanf("%s", cacheFilePath);
	cacheHstb = read_cache(cacheFilePath, INIT_HSTB_SIZE);

	chash_visit(cacheHstb, (VisitorFunc)&print_cache_custom);

	FILE* text = fopen(argv[1], "r");	

	struct _Data data = data_make(trie, cacheHstb);

	while((len = get_text_word(text, buff, &line))){
		cacheSearch.wrd = buff;
		flag = 1;
		status = trie_search(trie, buff, len);
		cache = chash_search(cacheHstb, (void*) &cacheSearch);
		if (!status && !cache) {
			cache = sugg_look_up(buff, len, &data);
			print_text_suggestions(argv[2], cache, line);
			print_cache_data(cacheFilePath, cache);
			chash_insert(cacheHstb, (void*)cache);
			flag = 0;
		}
		if (!status && flag)
			print_text_suggestions(argv[2], cache, line);
	}

	fclose(text);
	trie_destroy(trie);
	return 0;	


}

