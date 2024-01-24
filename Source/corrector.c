#include "corrector.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* FuncVisit
 */
void sugg_look_up_1(char* word, int len, Data data){
	if (data->flag)
		return;
	if ( cache_is_sugg(data->cache, word) && trie_search(data->dict, word, len) )
		data->flag = cache_add_sugg(data->cache, word, len);
	if (data->dist != MAX_DISTANCES) {
		Word new_word = word_make(word, len);
		chash_insert(data->hstb[data->dist], (void *) new_word);
	}
}

/* FuncVisit2
 */
void sugg_look_up_2(char* word, int len1, int len2, Data data) {
	if (data->flag){
		return;
	}
	if (cache_is_sugg(data->cache, word) &&
			(trie_search(data->dict, word, len1) ) &&
			(trie_search(data->dict, word + len1 + 1, len2))) {
		data->flag = cache_add_sugg(data->cache, word, len1 + len2 + 1);
	}
} 

struct _Data data_make(Trie trie, CHash cache_hstb){
	struct _Data new_data; 
	new_data.dict = trie;
	new_data.fun1 = (VisitFunc)sugg_look_up_1;
	new_data.fun2 = (VisitFunc2)sugg_look_up_2;
	new_data.hstb = malloc(sizeof(CHash) * MAX_DISTANCES);
	assert(new_data.hstb);
	new_data.hstb[0] = cache_hstb;
	new_data.flag = 0;
	new_data.dist = 0;
  return new_data;
}

void data_free(struct _Data data){
	trie_destroy(data.dict);
	chash_destroy(data.hstb[0]);
	free(data.hstb);
}

void data_add_cache(char* word, int len, Data data) {
	data->cache = cache_make(word, len);
}

void dist_all(char* word,int len, Data data) {
	dist_delet(word, len, data, data->fun1);
	dist_split(word, len,(char*) data->buff, data, data->fun2);
	dist_swap(word, len, data, data->fun1);
	dist_insert(word, len,(char*) data->buff, data, data->fun1);
	dist_remplace(word, len, data, data->fun1);
}

void dist_all_visit(Word word, Data data){
	dist_all(word_string(word), word_len(word), data);
}
	
Cache data_reset(Data data) {
	if (data->dist == MAX_DISTANCES){
		for(int i = 1; i < MAX_DISTANCES; i++)
			chash_destroy(data->hstb[i]);
	} else{
		for(int i = 1; i <= data->dist; i++)
			chash_destroy(data->hstb[i]);
	}
	
	data->flag = 0;
	data->dist = 0;
	return data->cache;
}

Cache sugg_look_up(char* word, int len, Data data){
	data_add_cache(word, len, data);
	data->hstb[++data->dist] = word_hstb_make();
	dist_all(word, len, data);

	while(data->dist < MAX_DISTANCES  && !data->flag) {
		if(++data->dist != MAX_DISTANCES)
			data->hstb[data->dist] = word_hstb_make();
		chash_visit_extra(data->hstb[data->dist - 1],
				              (void*) data, (VisitExtFunc) dist_all_visit);
	}
	return data_reset(data);
}
