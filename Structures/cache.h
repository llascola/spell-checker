#ifndef __CACHE__
#define __CACHE__
#define MAX_SUGGESTIONS 5
#define NOT_CACHED 0
#define CACHED 1
#include "../Source/utils.h"

struct _Cache {
	int n_suggs;
	char cached;
	char *wrd;
	char **suggs;
};

typedef struct _Cache* Cache;

Cache cache_make(char* word, int len, char cached);

int cache_add_sugg(Cache cache, char* sugg, int len); 

int cache_n_sugg(Cache cache);

char** cache_sugg(Cache cache);

void cache_destroy(Cache* cache); 

int cache_compare(Cache cache1, Cache cache2);

#endif

