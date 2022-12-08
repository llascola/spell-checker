#include "corrector.h"

Data data_make(Trie trie, CHash cache_hstb, char* word, int len){
	Data new_data = malloc(sizeof(struct _Data));
	new_data->dict = trie;
  new_data->cache = cache_make(word, len, NOT_CACHED);
	new_data->flag = 0;
	new_data->dist = 0;
	new_data->hstb = calloc(MAX_DISTANCES , sizeof(CHash) * MAX_DISTANCES);
	new_data->hstb[0] = cache_hstb;
  return new_data;
}

void sugg_look_up_1(char* word, int len, Data data){
	if (data->flag)
		return;
	if (trie_search(data->dict, word, len) == *"d")
		data->flag = cache_add_sugg(data->cache, word, len);
	if (data->dist != MAX_DISTANCES) {
		Word new_word = word_make(word, len);
		chash_insert(data->hstb[data->dist], (void *) new_word);
	}
}

void sugg_look_up_2(char* word, int len1, int len2, Data data) {
	if (data->flag){
		return;
	}
	if ((trie_search(data->dict, word, len1) == *"d") &&
			(trie_search(data->dict, word + len1 + 1, len2) == *"d")) {
		data->flag = cache_add_sugg(data->cache, word, len1 + len2);
	}
} 

void dist_all(char* word,int len, char* buff,
							Data data,
							VisitFunc sugg_look_up_1,
							VisitFunc2 sugg_look_up_2) {
	dist_delet(word, len, data, sugg_look_up_1);
	dist_split(word, len, buff, data, sugg_look_up_2);
	dist_swap(word, len, data, sugg_look_up_1);
	dist_insert(word, len, buff, data, (VisitFunc) sugg_look_up_1);
	dist_remplace(word, len, data, sugg_look_up_1);
}

Cache sugg_look_up(char* word, int len, int line, Trie dict, CHash cache){
	Data data = data_make(dict, cache, word, len);
	char buff[255];
	data->hstb[++data->dist] = word_hstb_make();
	dist_all(word, len, buff, data,(VisitFunc) sugg_look_up_1,(VisitFunc2) sugg_look_up_2);
	for(int i = 1; i <= MAX_DISTANCES; i++) {
		chash_visit(data->hstb[i], )
	}
}
