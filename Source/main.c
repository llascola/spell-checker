#include <stdio.h>
#include "io.h"
#include "corrector.h"

int main(int argc, char* argv[]) {
	char buff[255];
	int line;
	int len;
	int flag;
	char status;
	Cache cache;
	Trie trie = trie_make();	
	CHash cacheHstb;
	printf("Insert dictionary's file path: ");
	scanf("%s", buff);
	read_dictionary(buff, trie);
	printf("Insert cache's file path: ");
	scanf("%s", buff);
	cacheHstb = read_cache(buff, INIT_HSTB_SIZE);
	FILE* text = fopen("./text.txt", "r");	
	struct _Data data = data_make(trie, cacheHstb);
	while((len = get_text_word(text, buff, &line))){
		flag = 1;
		status = trie_search(trie, buff, len);
		if (!status) {
			cache = sugg_look_up(buff, len, &data);
			print_text_suggestions("./suggestions.txt", cache, line);
			print_cache_data("./cache.txt", cache);
			chash_insert(cacheHstb, (void*)cache);
			flag = 0;
		}
		if ((cache = chash_search(cacheHstb, buff)) && flag){
			print_text_suggestions("./suggestions.txt", cache, line);
		}
	}
	return 0;	


}
