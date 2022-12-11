#include <stdio.h>
#include <assert.h>
#include "io.h"
#include "corrector.h"

void print_cache_custom(Cache cach){
	printf("%s-----\n",cach->wrd);
}



int main(int argc, char* argv[]) {
	assert(argc == 3);
	char buff[255];
	char cacheFilePath[255];
	int line;
	int len;
	int flag;
	char status;
	Cache cache;
	struct _Cache cacheSearch;
	Trie trie = trie_make();	
	CHash cacheHstb;
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
		if (!status && !(cache = chash_search(cacheHstb, (void*) &cacheSearch))) {
			cache = sugg_look_up(buff, len, &data);
			print_text_suggestions(argv[2], cache, line);
			print_cache_data(cacheFilePath, cache);
			chash_insert(cacheHstb, (void*)cache);
			flag = 0;
		}
		if (flag && !status)
			print_text_suggestions(argv[2], cache, line);
	}
	trie_destroy(trie);
	return 0;	


}
