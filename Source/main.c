#include <stdio.h>
#include <assert.h>
#include "io.h"
#include "corrector.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	assert(argc == 3);

	char buff[255];  
	char cacheFilePath[255];

	int line = 1;
	int len;
	int flag;

	char status;
	
	Cache cache ;
	struct _Cache cacheSearch;  // Estructura cache inicializada es stack para búsqueda.

	Trie trie = trie_make();	
	CHash cacheHstb;

	printf("Ingrese la ruta del diccionario: ");
	scanf("%s", buff);
	read_dictionary(buff, trie);

	printf("Ingrese la ruta de la cache: ");
	scanf("%s", cacheFilePath);
	cacheHstb = read_cache(cacheFilePath);


	FILE* text = fopen(argv[1], "r");	
	struct _Data data = data_make(trie, cacheHstb);

	while((len = get_text_word(text, buff, &line))){
		cacheSearch.wrd = buff;
		flag = 1;
		status = trie_search(trie, buff, len);
		cache = chash_search(cacheHstb, (void*) &cacheSearch);
		if (!status && !cache) {
			cache = sugg_look_up(buff, len, &data);
			print_text_suggestions(argv[2], cache, line);
			print_cache_data(cacheFilePath, cache);
			chash_insert(cacheHstb, (void*)cache);
			flag = 0;
		}
		if (!status && flag)
			print_text_suggestions(argv[2], cache, line);
	}
	
	printf("Sugerencias generadas.\n");

	fclose(text);
	data_free(data);
	return 0;	


}
