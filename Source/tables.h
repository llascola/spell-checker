#ifndef __TABLES__
#define __TABLES__
#define	WORD_HSTB_SIZE 100000 
#define	CACHE_HSTB_SIZE 100000 
#include "../Structures/hash_ch.h"
#include "../Structures/cache.h"
#include "../Structures/word.h"
#include "utils.h"


CHash cache_hstb_make();

CHash word_hstb_make(); 
#endif

