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
	int dist;
	int flag;
	int len;
	int line;
	VisitFunc fun1;
	VisitFunc2 fun2;
};

typedef struct _Data* Data;

Data data_make(Trie trie, CHash cache_hstb, char* word, int len);

#endif
