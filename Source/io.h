#ifndef __INPUT_OUPUT__
#define __INPUT_OUPUT__
#include <stdio.h>
#include "../Structures/trie.h"
#include "tables.h"

/* *
 * Recibe una estructura de archivo inicializada.
 * Devuelve en el buffer la palabra leida y el *line
 * la linea en cual se encuentra en el texto.
 * Retorna la cantidad de caracteres leidos (longitud de palabra)
 * */
int get_text_word(FILE* text, char* buff, int *line); 

/* *
 * Toma la ruta de archivo de un diccionario y retorna una estructura
 * Trie inicializada.
 * */
void read_dictionary(char* dictFilePath, Trie trie);

/* *
 * Toma la ruta de archivo de la cache y retorna una estructura
 * CHash (Tabla hash con encadenamiento) inicializada.
 * */
CHash read_cache(char* cacheFilePath);

/* *
 * Imprime las sugerencias que se encuentra en la estructura cache pasada por 
 * parámetro en el archivo que se encuentra en suggestionFilePath.
 * */
void print_text_suggestions(const char* suggestionFilePath, Cache cache, int line);

/* *
 * Guarda la información de la estructura cache en cacheFilePath.
 * */

void print_cache_data(const char* cacheFilePath, Cache cache);

#endif

