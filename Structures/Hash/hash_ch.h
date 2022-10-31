#ifndef __HASHTB_CH_H__
#define __HASHTB_CH_H__
#include "../DList/dlist.h"

typedef unsigned int (*HashFunc)(void *data, int sizeTable);

typedef struct _CHash {
	unsigned int buckets;
	unsigned int sizeTable;
	DList* table;
	CopyFunc cpyf;
	DestroyFunc dstf;
	VisitorFunc vistf;
	CompareFunc cmpf;
	HashFunc hashf;
} CHash;


CHash chash_make(unsigned int buckets, CompareFunc cpyf, DestroyFunc dstf, 
								 VisitorFunc vistf, CompareFunc cmpf, HashFunc hashf);

void chash_destroy(CHash hstb);

int chash_insert(CHash hstb, void* data);

int chash_search(CHash hstb, void* data);

int chash_delete(CHash hstb, void* data);

int chash_rehash(CHash hstb);




#endif
