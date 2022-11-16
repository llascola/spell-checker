#include "hash_ch.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

CHash chash_make(int buckets, CopyFunc cpyf, DestroyFunc dstf, 
		 CompareFunc cmpf, HashFunc hashf) {
	CHash hstb;
	assert((hstb = malloc(sizeof(struct _CHash))));
	assert((hstb->table = calloc(buckets, sizeof(DList))));
	hstb->elements = 0;
	hstb->buckets = buckets;
	hstb->hashf = hashf;
	hstb->cmpf  = cmpf;
	hstb->dstf  = dstf;
	hstb->cpyf  = cpyf;
	return hstb;
}

void chash_destroy(CHash hstb) {
	for (int i = 0; i < hstb->buckets; i++)
		if (hstb->table[i] != NULL)
			dlist_destroy(&hstb->table[i], hstb->dstf);
	free(hstb->table);
}

void chash_insert_tour(void* data, void* hstb) {
	int i = ((CHash)hstb)->hashf(data) % ((CHash)hstb)->buckets;
if (((CHash)hstb)->table[i]
	dlist_insert(((CHash)hstb)->table[i], data, ((CHash)hstb)->cpyf, BACKWARD);
	return;
}

int chash_rehash(CHash hstb) {
	if((100 * hstb->elements) >= (75 * hstb->buckets)) {
		int oldSize = hstb->buckets;
		hstb->buckets = hstb->buckets * 2;
		DList *tmp = hstb->table;
		hstb->table = calloc(hstb->buckets, sizeof(DList));
		for(int i = 0; i < oldSize; i++) {
			dlist_tour_ext(tmp[i], chash_insert_tour, (void*) hstb, FORWARD);
			dlist_destroy(&tmp[i], hstb->dstf);
		}
		free(tmp);
		return 1;
	} else
		return 0;
}


int chash_insert(CHash hstb, void* data) {
	chash_rehash(hstb);
	int i = (int)hstb->hashf(data) % hstb->buckets;
	printf("%d\n", i);
	if (hstb->table[i] == NULL) {
		hstb->table[i] = dlist_make();
		hstb->elements++;
		return dlist_insert(hstb->table[i], data, hstb->cpyf, BACKWARD);
	}
	if (dlist_search(hstb->table[i], data, hstb->cmpf)){
		hstb->elements++;
		return dlist_insert(hstb->table[i], data, hstb->cpyf, BACKWARD);
	}
	else 
		return 1;
}


int chash_search(CHash hstb, void* data) {
	int i = hstb->hashf(data) % hstb->buckets;
	return dlist_search(hstb->table[i], data, hstb->cmpf);
}

int chash_delete(CHash hstb, void* data) {
	int i = hstb->hashf(data) % hstb->buckets;
	if (dlist_delete(hstb->table[i], data, hstb->cmpf, hstb->dstf))
		return 1;
	else
		hstb->elements--;
	return 0;
}

void chash_visit(CHash hstb, VisitorFunc vistif) {
	for (int i = 0; i < hstb->buckets; i++) 
		if (hstb->table[i] != NULL)
			dlist_tour(hstb->table[i], vistif, FORWARD);
}
