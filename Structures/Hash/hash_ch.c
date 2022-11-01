#include "hash_ch.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

CHash chash_make(unsigned int buckets, CopyFunc cpyf, DestroyFunc dstf, 
		 CompareFunc cmpf, HashFunc hashf) {
	CHash hstb;
	assert((hstb = malloc(sizeof(struct _CHash))));
	assert((hstb->table = calloc(buckets, sizeof(DList))));
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

int chash_rehash(CHash hstb) {
	if((100 * hstb->elements) >= (75 * hstb->buckets)) {
		unsigned int oldSize = hstb->buckets;
		hstb->buckets = hstb->buckets * 2;
		DList *tmp = hstb->table;
		hstb->table = calloc(hstb->buckets, sizeof(DList));
		for(int i = 0; i < oldSize; i++) {
			dlist_tour_ext(tmp[i], (VisitExtFunc)chash_insert, (void*) hstb, FORWARD);
			dlist_destroy(tmp[i], hstb->dstf);
		}
		free(tmp);
		return 1;
	} else
		return 0;
}

int chash_insert(void* data, void* hstb) {
	int i = ((CHash)hstb)->hashf(data, ((CHash)hstb)->buckets);
	if (dlist_search(((CHash)hstb)->table[i], data, ((CHash)hstb)->cmpf) && chash_rehash((CHash)hstb))
		return 0;
	else
		return dlist_insert(((CHash)hstb)->table[i], data, ((CHash)hstb)->cpyf, BACKWARD);
}


int chash_search(CHash hstb, void* data) {
	int i = hstb->hashf(data, hstb->buckets);
	return dlist_search(hstb->table[i], data, hstb->cmpf);
}

int chash_delete(CHash hstb, void* data) {
	int i = hstb->hashf(data, hstb->buckets);
	return dlist_delete(hstb->table[i], data, hstb->cmpf, hstb->dstf);
}
