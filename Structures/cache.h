#ifndef __CACHE__
#define __CACHE__
#define MAX_SUGGESTIONS 5
#include "utils.h"

struct _Cache {
	char *wrd;
	char *suggs[MAX_SUGGESTIONS];
	int n_suggs;
};

typedef struct _Cache* Cache;

Cache cache_make(char* wrd, char** sgg, int n_suggs);

void cache_destroy(Cache* cache); 

int cache_compare(Cache cache1, Cache cache2);

#endif

