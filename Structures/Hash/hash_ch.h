#ifndef __HASHTB_CH_H__
#define __HASHTB_CH_H__
#include "../DList/dlist.h"

typedef unsigned int (*HashFunc)(void *data, int sizeTable);

struct _CHash {
	unsigned int buckets;
	unsigned int elements;
	DList* table;
	CopyFunc cpyf;
	DestroyFunc dstf;
	CompareFunc cmpf;
	HashFunc hashf;
};
typedef struct _CHash* CHash;

CHash chash_make(unsigned int buckets, CopyFunc cpyf, DestroyFunc dstf, 
								 CompareFunc cmpf, HashFunc hashf);

void chash_destroy(CHash hstb);

int chash_insert(void* data,void* hstb);

int chash_search(CHash hstb, void* data);

int chash_delete(CHash hstb, void* data);

#endif
