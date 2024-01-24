#include "tables.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void *id(void *data) {
	return data;
}

unsigned cache_hash(Cache cache) {
	return hash(cache->wrd);
}

unsigned word_hash(Word distWord){
	return hash_len(distWord->word, distWord->len);
}

int cache_word_compare(Cache cache1, Cache cache2){
	return strcmp(cache1->wrd, cache2->wrd);
}

CHash cache_hstb_make(){
	return chash_make(CACHE_HSTB_SIZE,
										(CopyFunc) &id,
										(DestroyFunc) &cache_destroy,
										(CompareFunc) &cache_word_compare,
										(HashFunc) &cache_hash);
}

CHash word_hstb_make() {
	CHash distHstb = chash_make(WORD_HSTB_SIZE,
															&id,
															(DestroyFunc) &word_dest,
															(CompareFunc) &word_compare,
															(HashFunc) &word_hash); 
	return distHstb;
}
