#ifndef __DISTANCES__
#define __DISTANCES__
#define INIT_HSTB_SIZE 1500
#include "../Structures/Hash/hash_ch.h"
#include "utils.h"

struct _Word{
	char* word;
	int len;
};

typedef struct _Word* Word;


CHash dist_hstb_make();

#endif
