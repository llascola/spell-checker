#include "hash_ch.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

static inline void *id(void* data){return data;}

static inline void null(__attribute__((unused))void* data) { return; }

CHash chash_make(unsigned buckets, CopyFunc cpyf, DestroyFunc dstf, 
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
	for (unsigned i = 0; i < hstb->buckets; i++)
		if (hstb->table[i] != NULL)
			dlist_destroy(&hstb->table[i], hstb->dstf);
	free(hstb->table);
	free(hstb);
}

void chash_insert_tour(void* data, CHash hstb) {
	unsigned i = hstb->hashf(data) % ((CHash)hstb)->buckets;
	if (hstb->table[i] == NULL)
		hstb->table[i] = dlist_make();
	dlist_insert(hstb->table[i], data, id, BACKWARD);
	return;
}

int chash_rehash(CHash hstb) {
	if((100 * hstb->elements) >= (75 * hstb->buckets)) {
		unsigned oldSize = hstb->buckets;
		hstb->buckets = hstb->buckets * 2;
		DList *tmp = hstb->table;
		hstb->table = calloc(hstb->buckets, sizeof(DList));
		for(unsigned i = 0; i < oldSize; i++) {
			if ( tmp[i] != NULL ) {
				dlist_tour_ext(tmp[i],(VisitExtFunc) chash_insert_tour, (void*) hstb, FORWARD);
				dlist_destroy(&tmp[i], null);
			}
		}
		free(tmp);
		return 1;
	} else
		return 0;
}


int chash_insert(CHash hstb, void* data) {
	chash_rehash(hstb);
	unsigned i = (unsigned)hstb->hashf(data) % hstb->buckets;
	if (hstb->table[i] == NULL) {
		hstb->table[i] = dlist_make();
		hstb->elements++;
		return dlist_insert(hstb->table[i], data, hstb->cpyf, BACKWARD);
	}
	hstb->elements++;
	return dlist_insert(hstb->table[i], data, hstb->cpyf, BACKWARD);
}

void* chash_search(CHash hstb, void* data) {
	unsigned i = (unsigned)hstb->hashf(data) % hstb->buckets;
	return dlist_search(hstb->table[i], data, hstb->cmpf);
}

int chash_delete(CHash hstb, void* data) {
	unsigned i = (unsigned)hstb->hashf(data) % hstb->buckets;
	if (dlist_delete(hstb->table[i], data, hstb->cmpf, hstb->dstf))
		return 1;
	else
		hstb->elements--;
	return 0;
}

void chash_visit(CHash hstb, VisitorFunc vistif) {
	for (unsigned i = 0; i < hstb->buckets; i++) 
		if (hstb->table[i] != NULL)
			dlist_tour(hstb->table[i], vistif, FORWARD);
}

void chash_visit_extra(CHash hstb, void* data, VisitExtFunc vistif) {
	for (unsigned i = 0; i < hstb->buckets; i++) 
		if (hstb->table[i] != NULL)
			dlist_tour_ext(hstb->table[i], vistif, data, FORWARD);
}
