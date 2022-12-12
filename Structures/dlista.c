#include "dlista.h"
#include <stdlib.h>
#include <stdio.h>

DLista dlist_crear() {
  DLista lista;
  lista.primero = NULL;
  lista.ultimo = NULL;
  return lista;
}

int dlist_vacia(DLista lista) {
  if (lista.primero == NULL)
    return 1;
  return 0;
}

void dlist_destruir(DLista lista, FuncionDestruir destruir) {
  DNodo *nodoDestruir, *nodo = lista.primero;
  while (nodo != NULL) {
    nodoDestruir = nodo;
    nodo = nodo->sig;
    destruir(nodoDestruir->dato);
    free(nodoDestruir);
  }
}

void dlist_recorrer(DLista lista, FuncionVisitar visitar,
                    DListaOrdenDeRecorrido orden) {
  DNodo *nodo =
      orden == DLIST_RECORRIDO_HACIA_ADELANTE ? lista.primero : lista.ultimo;
  while (nodo != NULL) {
    visitar(nodo->dato);
    nodo = orden == DLIST_RECORRIDO_HACIA_ADELANTE ? nodo->sig : nodo->ant;
  }
}

void dlist_recorrer_extra(DLista lista, FuncionVisitarExtra visitar,
                          void* extra, DListaOrdenDeRecorrido orden) {
  DNodo *nodo =
      orden == DLIST_RECORRIDO_HACIA_ADELANTE ? lista.primero : lista.ultimo;
  while (nodo != NULL) {
    visitar(nodo->dato, extra);
    nodo = orden == DLIST_RECORRIDO_HACIA_ADELANTE ? nodo->sig : nodo->ant;
  }
}

DLista dlist_insertar_inicio(DLista lista, void *dato, FuncionCopiar copiar) {
  DNodo *nuevoNodo = malloc(sizeof(DNodo));
  nuevoNodo->ant = NULL;
  nuevoNodo->dato = copiar(dato);
  if (lista.primero == NULL) {
    nuevoNodo->sig = NULL;
    lista.ultimo = nuevoNodo;
  } else {
    nuevoNodo->sig = lista.primero;
    lista.primero->ant = nuevoNodo;
  }
  lista.primero = nuevoNodo;
  return lista;
}

DLista dlist_insertar_final(DLista lista, void *dato, FuncionCopiar copiar) {
  DNodo *nuevoNodo = malloc(sizeof(DNodo));
  nuevoNodo->sig = NULL;
  nuevoNodo->dato = copiar(dato);
  if (lista.primero == NULL) {
    nuevoNodo->ant = NULL;
    lista.primero = nuevoNodo;
  } else {
    nuevoNodo->ant = lista.ultimo;
    lista.ultimo->sig = nuevoNodo;
  }
  lista.ultimo = nuevoNodo;
  return lista;
}

void *dlist_dato(DLista lista, unsigned int pos, FuncionCopiar copiar) {
  if (lista.primero == NULL)
    return NULL;
  DNodo *nodo;
  for (nodo = lista.primero; nodo->sig != NULL && pos > 0;
       nodo = nodo->sig, pos--);
  return copiar(nodo->dato);
}

void *dlist_busqueda(DLista lista, void *dato,
										 FuncionComparadora compara,
										 FuncionCopiar copia) {
	if (lista.primero == NULL)
		return NULL;
	int bandera;
	DNodo *nodo;
	for (nodo = lista.primero; (bandera = compara(dato, nodo->dato)) && nodo->sig != NULL ;
			 nodo = nodo->sig);
	return bandera?NULL:copia(nodo->dato);
}

/**
 * Elimina el nodo de la posici\u00f3n dada.
 * Si pos >= largo(lista), elimina el \u00faltimo nodo.
 */
DLista dlist_eliminar(DLista lista, void* dato,FuncionComparadora compara, FuncionDestruir destruir) {
  if (lista.primero == NULL)
    return lista;
  else if (lista.primero == lista.ultimo && !compara(dato, lista.primero->dato)) {
    destruir(lista.primero->dato);
    free(lista.primero);
    lista.primero = NULL;
    lista.ultimo = NULL;
    return lista;
  }
	
  DNodo *nodo = lista.primero;
	int bandera = compara(dato, nodo->dato);

  for (;bandera && nodo->sig != NULL ; nodo = nodo->sig)
		bandera = compara(dato, nodo->dato);
	if (!bandera)	
		return lista;
	nodo->ant->sig = nodo->sig;
	if (nodo->sig == NULL)
		lista.ultimo = nodo->ant;
	destruir(nodo->dato);
  free(nodo);
  return lista;
}

/**
 * Devuelve una copia de la lista en orden reverso.
 */
DLista dlist_copiar_reversa(DLista lista, FuncionCopiar copia) {
  DLista lista_copia = dlist_crear();
  if (!dlist_vacia(lista)) {
    for (DNodo * nodo = lista.primero; nodo != NULL; nodo = nodo->sig)
      lista_copia = dlist_insertar_inicio(lista_copia, nodo->dato, copia);
  }
  return lista_copia;
}

/**
 * Copia los datos de la lista en el buff pasado desde la posici\u00f3n, 
 * al finalizar el entero pos apunta a la pr\u00f3xima posici\u00f3n a sin escribir.
 */
void copiar_en_buff(DLista lista, char *buff, int *pos) {
  for (DNodo * nodo = lista.primero; nodo != NULL; nodo = nodo->sig) {
    buff[*pos] = *(char *) nodo->dato;
    *pos += 1;
  }
}
