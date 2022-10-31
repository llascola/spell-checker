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
	int i = hstb->hashf(data, hstb->buckets);
	if (dlist_search(hstb->table[i], data, hstb->cmpf))
		return 0;
	else
		return dlist_insert(hstb->table[i], data, hstb->cpyf, BACKWARD);
}

int chash_search(CHash hstb, void* data) {
	int i = hstb->hashf(data, hstb->buckets);
	return dlist_search(hstb->table[i], data, hstb->cmpf);
}

int chash_delete(CHash hstb, void* data) {
	int i = hstb->hashf(data, hstb->buckets);
	return dlist_delete(hstb->table[i], data, hstb->cmpf, hstb->dstf);
}
