#include "trie.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Trie trie_make() {
	Trie t = malloc(sizeof(struct _TNode));
	assert(t);
	for (int i = 0; i < NUM_CHARS; i++) 
		t->chars[i] = NULL;
	t->terminal = false;
	return t;
}

void trie_destroy(Trie t) {
	for(int i = 0; i < NUM_CHARS; i++) {
		if (t->chars[i] != NULL)
			trie_destroy(t->chars[i]);
	}
	free(t);
}

bool trie_insert(Trie *t_root, char *wrd) {
	if (*t_root == NULL) 
		*t_root = trie_make();

	Trie tmp = *t_root;
	int length = strlen(wrd);

	for (int i = 0; i < length; i++) {
		unsigned char c = wrd[i];
		if (tmp->chars[c] == NULL)
			tmp->chars[c] = trie_make();
		tmp = tmp->chars[c];
	}
	return tmp->terminal = true;
}

bool trie_search(Trie t_root, char *wrd) {
	int length = strlen(wrd);
	Trie tmp = t_root;
	for (int i = 0; i < length; i++) {
		if (tmp->chars[wrd[i]] == NULL) 
			return false;
		tmp = tmp->chars[wrd[i]];
	}
	return tmp->terminal;
}

bool trie_delete(Trie *t_root, char *wrd) {
	int length = strlen(wrd);
	Trie tmp = *t_root;
	for (int i = 0; i < length; i++) {
		if (tmp->chars[wrd[i]] == NULL) 
			return true;
		tmp = tmp->chars[wrd[i]];
	}
	return !(tmp->terminal = false);
}




