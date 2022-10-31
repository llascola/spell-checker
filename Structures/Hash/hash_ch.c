#include "hash_ch.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

CHash chash_make(unsigned int buckets, CopyFunc cpyf, DestroyFunc dstf, 
		 CompareFunc cmpf, HashFunc hashf) {
	CHash hstb;
	assert((hstb = malloc(sizeof(struct _CHash))));
	assert((hstb->table = calloc(buckets, sizeof(DList) * buckets)));
	hstb->elements = 0;
	hstb->hashf = hashf;
	hstb->cmpf  = cmpf;
	hstb->dstf  = dstf;
	hstb->cpyf  = cpyf;
	return hstb;
}

void chash_destroy(CHash hstb) {
	for (int i = 0; i < hstb->buckets; i++)
		dlist_destroy(hstb->table[i], hstb->dstf);
}

int chash_insert(CHash hstb, void* data) {
	dlist_insert(hstb->table[hstb->hashf(data, hstb->buckets)], data, hstb->cpyf,
							 BACKWARD);
}
