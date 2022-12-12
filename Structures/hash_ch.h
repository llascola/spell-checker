#ifndef __HASHTB_CH_H__
#define __HASHTB_CH_H__
#include "dlist.h"
#include "dlista.h"

typedef int (*HashFunc)(void *data);

struct _CHash {
	unsigned buckets;
	unsigned elements;
	DLista* table;
	CopyFunc cpyf;
	DestroyFunc dstf;
	CompareFunc cmpf;
	HashFunc hashf;
};

typedef struct _CHash* CHash;

CHash chash_make(unsigned buckets, CopyFunc cpyf, DestroyFunc dstf, 
								 CompareFunc cmpf, HashFunc hashf);

void chash_destroy(CHash hstb);

int chash_insert(CHash hstb, void* data);

void* chash_search(CHash hstb, void* data);

int chash_delete(CHash hstb, void* data);

void chash_visit(CHash hstb, VisitorFunc vistif); 

void chash_visit_extra(CHash hstb, void* data, VisitExtFunc vistif); 
#endif
