#ifndef __HASHTB_CH_H__
#define __HASHTB_CH_H__
#include "../DList/dlist.h"

typedef int (*HashFunc)(void *data);

struct _CHash {
	int buckets;
	int elements;
	DList* table;
	CopyFunc cpyf;
	DestroyFunc dstf;
	CompareFunc cmpf;
	HashFunc hashf;
};

typedef struct _CHash* CHash;

CHash chash_make(int buckets, CopyFunc cpyf, DestroyFunc dstf, 
								 CompareFunc cmpf, HashFunc hashf);

void chash_destroy(CHash hstb);

int chash_insert(CHash hstb, void* data);

int chash_search(CHash hstb, void* data);

int chash_delete(CHash hstb, void* data);

void chash_visit(CHash hstb, VisitorFunc vistif); 

#endif
