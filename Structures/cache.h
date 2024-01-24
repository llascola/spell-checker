#ifndef __CACHE__
#define __CACHE__
#define MAX_SUGGESTIONS 5
#include "../Source/utils.h"

struct _Cache {
	int n_suggs;
	char *wrd;
	char **suggs;
};

typedef struct _Cache* Cache;

/***
 * Inicializa la estructura "Cache" con
 * la palabra y la longitud ingresada como parametro.
 ***/
Cache cache_make(char* word, int len);

/***
 * Agrega una sugerencia a la estructura cache.
 ***/
int cache_add_sugg(Cache cache, char* sugg, int len); 

/**
 * Retorna el número de sugerencias.
 **/
int cache_n_sugg(Cache cache);

/**
 * Retorna el arreglo de sugerencias
 **/
char** cache_sugg(Cache cache);

/**
 * Destruye la estructura cache
 **/
void cache_destroy(Cache cache); 

/**
 * Funcion comparadora entre dos estructuras de
 * tipo Cache.
 **/

int cache_compare(Cache cache1, Cache cache2);

/**
 * Retorna 0 si la palabra sugg ingresada como
 * parametro esta en el arreglo de sugerencias.
 * Si no esta retorna un entero no nulo.
 **/
int cache_is_sugg(Cache cache, char* sugg);

#endif

