#ifndef __TABLES__
#define __TABLES__
#define	INIT_HSTB_SIZE 1555
#include "../Structures/hash_ch.h"
#include "../Structures/cache.h"
#include "../Structures/word.h"
#include "utils.h"

CHash cache_hstb_make(int table_size);

CHash word_hstb_make(); 
#endif

