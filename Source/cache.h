#ifndef __CACHE__
#define __CACHE__
#define MAX_SUGGESTIONS 5
#include "../Structures/Hash/hash_ch.h"
#include "utils.h"

struct _Cache {
	char *wrd;
	char *suggs[MAX_SUGGESTIONS];
	int n_suggs;
};

typedef struct _Cache* Cache;

Cache cache_make(char* wrd, char** sgg, int n_suggs);

void cache_destroy(Cache* cache);

CHash cache_hstb_make(int table_size);

#endif

