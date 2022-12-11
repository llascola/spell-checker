#include "cache.h"
#include <stdlib.h>
#include <string.h>

Cache cache_make(char* word, int len){
	Cache new_cache = malloc(sizeof(struct _Cache));
	new_cache->wrd = malloc(sizeof(char) * (len + 1));
	memcpy(new_cache->wrd, word, len);
	new_cache->wrd[len] = 0;
	new_cache->suggs = calloc(MAX_SUGGESTIONS, sizeof(char*) * MAX_SUGGESTIONS);
	new_cache->n_suggs = 0;

	return new_cache;
}

inline int cache_n_sugg(Cache cache) {
	return cache->n_suggs;
}

inline char** cache_sugg(Cache cache) {
	return cache->suggs;
}

int cache_add_sugg(Cache cache, char* sugg, int len){
	int n_suggs = cache->n_suggs;
	if (cache->n_suggs == MAX_SUGGESTIONS) {
		return 1;
	}
	cache->suggs[n_suggs] = malloc(sizeof(char) * (len + 1));
	memcpy(cache->suggs[n_suggs], sugg, len);
	cache->suggs[n_suggs][len] = 0;
	cache->n_suggs++;
	return 0;
}

void cache_destroy(Cache cache) {
	free(cache->wrd);
	for (int i = 0; i < cache->n_suggs; i++)
		free(cache->suggs[i]);
	free(cache->suggs);
	free(cache);
}

int cache_compare(Cache cache1, Cache cache2) {
	return strcmp(cache1->wrd, cache2->wrd);
}



