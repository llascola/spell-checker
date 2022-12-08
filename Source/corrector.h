#ifndef __CORRECTOR__
#define __CORRECTOR__
#define MAX_DISTANCES 3
#include "dist.h"
#include "tables.h"
#include "../Structures/Trie/trie.h"
#include "../Structures/cache.h"
#include "../Structures/word.h"

struct _Data {
	Trie dict;
	Cache cache;
	CHash *hstb;
	VisitFunc fun1;
	VisitFunc2 fun2;
	int dist;
	int flag;
	int len;
	int line;
	char* buff[255];
};

typedef struct _Data* Data;

struct _Data data_make(Trie trie, CHash cache_hstb);

Cache sugg_look_up(char* word, int len, Data data);

#endif
