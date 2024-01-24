#ifndef __CORRECTOR__
#define __CORRECTOR__
#define MAX_DISTANCES 3
#include "dist.h"
#include "tables.h"
#include "../Structures/trie.h"
#include "../Structures/cache.h"
#include "../Structures/word.h"

struct _Data {
	Trie dict;
	Cache cache;
	CHash *hstb;
	VisitFunc fun1;
	VisitFunc2 fun2;
	int dist;
	int flag;
	int len;
	int line;
	char* buff[255];
};


typedef struct _Data* Data;

/* *
 * Genera la estructura que contiene los datos necesarios 
 * para la ejecución del algoritmo sugg_look_up
 * */
struct _Data data_make(Trie trie, CHash cache_hstb);

/* *
 * Algorimo de busqueda de sugerencias.
 * Toma una palabra, su longitud y la estructura Data.
 * Retorna una estructura Cache de la palabra ingresada.
 * */
Cache sugg_look_up(char* word, int len, Data data);

/* *
 * Libera los datos allocados en Data
 * */
void data_free(struct _Data data);

#endif
