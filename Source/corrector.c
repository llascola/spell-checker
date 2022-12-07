#include "corrector.h"

Data data_make(Trie* trie, CHash* cache_hstb, char* word, int len){
	Data new_data = malloc(sizeof(struct _Data));
	new_data->dict = *trie;
  new_data->cache = cache_make(word, len, NOT_CACHED);
	new_data->flag = 0;
	new_data->dist = 1;
	new_data->hstb = calloc(MAX_DISTANCES , sizeof(CHash) * MAX_DISTANCES);
	new_data->hstb[0] = *cache_hstb;
  return new_data;
}

void sugg_look_up(char* word, int len, int stop, Data data){
	if (!data->flag){
		if (trie_search(data->dict, word, len) == *"d")
			data->flag = cache_add_sugg(data->cache, word, len);
		if (stop) {
			Word new_word = word_make(word, len);
			chash_insert(data->hstb[data->dist], (void *) new_word);
		}

	}
}
