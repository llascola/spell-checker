#include "hash_ch.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


inline static void *id(void* data) { return data; }

inline static void null(__attribute__((unused)) void *data) { return; }

CHash chash_make(unsigned buckets, CopyFunc cpyf, DestroyFunc dstf, 
		 CompareFunc cmpf, HashFunc hashf) {
	CHash hstb;
	assert((hstb = malloc(sizeof(struct _CHash))));
	assert((hstb->table = malloc(sizeof(DLista) * buckets)));
	hstb->elements = 0;
	hstb->buckets = buckets;
	hstb->hashf = hashf;
	hstb->cmpf  = cmpf;
	hstb->dstf  = dstf;
	hstb->cpyf  = cpyf;

	for (unsigned i = 0; i < buckets; i++)
		hstb->table[i] = dlist_crear();

	return hstb;
}

void chash_destroy(CHash hstb) {
	for (unsigned i = 0; i < hstb->buckets; i++)
			dlist_destruir(hstb->table[i], hstb->dstf);
	free(hstb->table);
	free(hstb);
}

void chash_insert_tour(void* data, CHash hstb) {
	unsigned i = hstb->hashf(data) % hstb->buckets;
	hstb->table[i] = dlist_insertar_final(hstb->table[i], data, id);
	return;
}

int chash_rehash(CHash hstb) {
	if((100 * hstb->elements) >= (75 * hstb->buckets)) {
		unsigned oldSize = hstb->buckets;
		hstb->buckets = hstb->buckets * 2;
		DLista *tmp = hstb->table;
		hstb->table = malloc(sizeof(DList) * hstb->buckets);
	  for (unsigned i = 0; i < hstb->buckets; i++)
			hstb->table[i] = dlist_crear();
		for(unsigned i = 0; i < oldSize; i++) {
				dlist_recorrer_extra(tmp[i],(FuncionVisitarExtra) chash_insert_tour,
														 (void*) hstb, DLIST_RECORRIDO_HACIA_ADELANTE);
				dlist_destruir(tmp[i], null);
		}
		free(tmp);
		return 1;
	} else
		return 0;
}

/*
int chash_insert(CHash hstb, void* data) {
	chash_rehash(hstb);
	int i = (unsigned)hstb->hashf(data) % hstb->buckets;

	if (hstb->table[i] == NULL) {
		hstb->table[i] = dlist_make();
		hstb->elements++;
		return dlist_insert(hstb->table[i], data, hstb->cpyf, BACKWARD);
	}
	hstb->elements++;
	return dlist_insert(hstb->table[i], data, hstb->cpyf, BACKWARD);
}
*/
int chash_insert(CHash hstb, void* data) {
	chash_rehash(hstb);
	unsigned i = hstb->hashf(data) % hstb->buckets;
	hstb->table[i] = dlist_insertar_final(hstb->table[i], data, hstb->cpyf);
	return 0;
}

void* chash_search(CHash hstb, void* data) {
	unsigned i = hstb->hashf(data) % hstb->buckets;
	return dlist_busqueda(hstb->table[i], data, hstb->cmpf, hstb->cpyf);
}

int chash_delete(CHash hstb, void* data) {
	unsigned i = hstb->hashf(data) % hstb->buckets;
	hstb->table[i] = dlist_eliminar(hstb->table[i], data, hstb->cmpf, hstb->dstf);
	return 0;
}

void chash_visit(CHash hstb, VisitorFunc vistif) {
	for (unsigned i = 0; i < hstb->buckets; i++) 
			dlist_recorrer(hstb->table[i], vistif, DLIST_RECORRIDO_HACIA_ADELANTE);
}

void chash_visit_extra(CHash hstb, void* data, VisitExtFunc vistif) {
	for (unsigned i = 0; i < hstb->buckets; i++) 
			dlist_recorrer_extra(hstb->table[i], vistif, data, DLIST_RECORRIDO_HACIA_ADELANTE);
}
