#ifndef __HASHTB_CH_H__
#define __HASHTB_CH_H__
#include "dlist.h"

typedef int (*HashFunc)(void *data);

struct _CHash {
	unsigned buckets;
	unsigned elements;
	DList* table;
	CopyFunc cpyf;
	DestroyFunc dstf;
	CompareFunc cmpf;
	HashFunc hashf;
};

typedef struct _CHash* CHash;

/**
 * Inicializa la tabla hash. Toma la cantidad inicial de la tabla
 * y las respectivas funciones copiar, destruir, comparar y hashing.
 **/
CHash chash_make(unsigned buckets, CopyFunc cpyf, DestroyFunc dstf, 
								 CompareFunc cmpf, HashFunc hashf);

/**
 * Destruye la tabla hash
 **/
void chash_destroy(CHash hstb);

/**
 * Inserta un elemento en la tabla.
 * Esta función no chequea si el elemento esta
 * en la tabla.
 **/
int chash_insert(CHash hstb, void* data);

/**
 * Busca si un elemento pertenece a la tabla.
 * Devuelve NULL si el mismo no se encuetra.
 * En caso de ser encontrado se retorna el puntero al
 * dato que esta en la tabla
 * */
void* chash_search(CHash hstb, void* data);

/* *
 * Elimina el elemento de la tabla.
 * Retorna 0 si se eliminó con éxito.
 * Retorna -1 si no se encontró el dato a eliminar
 * */
int chash_delete(CHash hstb, void* data);
/**
 * Aplica una función a todos los elementos de la tabla
 * */
void chash_visit(CHash hstb, VisitorFunc vistif); 

/**
 * Aplica una función a todos los elementos de la tabla
 * con un dato extra pasado por parámetro.
 * */
void chash_visit_extra(CHash hstb, void* data, VisitExtFunc vistif); 
#endif
