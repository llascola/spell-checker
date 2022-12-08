#include <stdio.h>
#include "io.h"
#include "corrector.h"

int main(int argc, char* argv[]) {
	char buff[255];
	int line;
	int len;
	char status;
	Cache cache;
	Trie trie = trie_make();	
	CHash cacheHstb;
	printf("Insert dictionary's file path: ");
	scanf("%s", buff);
	read_dictionary(buff, trie);
	printf("Insert cache's file path: ");
	scanf("%s", buff);
	cacheHstb = read_cache(buff, INIT_HSTB_SIZE, trie);
	FILE* text = fopen("./text.txt", "r");	
	struct _Data data = data_make(trie, cacheHstb);
	while((len = get_text_word(text, buff, &line))){
		status = trie_search(trie, buff, len);
		if (!status) {
			cache = sugg_look_up(buff, len, &data);
			print_text_suggestions("./suggestions.txt", cache, line);
			print_cache_data("./cache.txt", cache);
			chash_insert(cacheHstb, (void*)cache);
			chash_visit
		}

	}
	


}
