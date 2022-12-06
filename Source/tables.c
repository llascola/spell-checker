#include "tables.h"
#include <stdlib.h>
#include <string.h>

void *id(void *data) {
	return data;
}

unsigned cache_hash(Cache cache) {
	return hash(cache->wrd);
}

unsigned word_hash(Word distWord){
	return hash_len(distWord->word, distWord->len);
}

CHash cache_hstb_make(int table_size){
	return chash_make(table_size,
										(CopyFunc) id,
										(DestroyFunc) cache_destroy,
										(CompareFunc) cache_compare,
										(HashFunc) cache_hash);
}

CHash word_hstb_make() {
	CHash distHstb = chash_make(INIT_HSTB_SIZE,
															id,
															(DestroyFunc) word_dest,
															(CompareFunc) word_compare,
															(HashFunc) word_hash); 
	return distHstb;
}
