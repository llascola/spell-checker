#include "cache.h"
#include <stdlib.h>
#include <string.h>

Cache cache_make(char* wrd, char* sgg, int n_suggs, int state){
	Cache new_cache = malloc(sizeof(struct _Cache));
	new_cache->wrd = wrd;
	new_cache->suggs = sgg;
	new_cache->n_suggs = n_suggs;
	new_cache->state = 0;
	return new_cache;
}

void cache_destroy(Cache* cache) {
	free((*cache)->wrd);
	free((*cache)->suggs);
	free(*cache);
}

int cache_compare(Cache cache1, Cache cache2) {
	return strcmp(cache1->wrd, cache2->wrd);
}

