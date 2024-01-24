#ifndef __DISTANCES__
#define __DISTANCES__

typedef void (*VisitFunc)(char* w, int len, void* data);
typedef void (*VisitFunc2)(char* w,  int len1, int len2, void* data);

/* Las funciones distancia modifican la palabra ingresada y aplican
 * VisitFunc a cada una de las transformaciones
 * */

/* *
 * Intercambia las letras adyacentes
 * */
int dist_swap(char *w, int len, void* data, VisitFunc func);

/* *
 * Inserta una letra entre letras
 * */
int dist_insert(char *w, int len, char* buff, void* data, VisitFunc func);

/* *
 * Elimina una letra
 * */
int dist_delet(char *w, int len, void* data,VisitFunc func);

/* *
 * Remplaza una letra por otro
 * */
int dist_remplace(char *w, int len, void* data, VisitFunc func);

/* *
 * Se agrega un espacio entre letras.
 * */
int dist_split(char *w, int len, char* buff, void* data, VisitFunc2 func); 

#endif
