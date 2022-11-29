#ifndef __CACHE__
#define __CACHE__

struct _Cache {
	char *wrd;
	char *suggs;
	int n_suggs;
	int state;
};

typedef struct _Cache* Cache;

Cache cache_make(char* wrd, char* sgg, int n_suggs, int state);

void cache_destroy(Cache* cache);

int cache_compare(Cache cache1, Cache cache2);

#endif

