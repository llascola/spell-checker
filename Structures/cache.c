#include "cache.h"
#include <stdlib.h>
#include <string.h>

Cache cache_make(char* wrd, char** sgg, int n_suggs){
	Cache new_cache = malloc(sizeof(struct _Cache));
	strcpy(new_cache->wrd, wrd);
	for (int i = 0; i < n_suggs; i++)
		strcpy(new_cache->suggs[i], sgg[i]);
	new_cache->n_suggs = n_suggs;
	return new_cache;
}

void cache_destroy(Cache* cache) {
	free((*cache)->wrd);
	for (int i = 0; i < (*cache)->n_suggs; i++)
		free((*cache)->suggs[i]);
	free(*cache);
}

int cache_compare(Cache cache1, Cache cache2) {
	return strcmp(cache1->wrd, cache2->wrd);
}



