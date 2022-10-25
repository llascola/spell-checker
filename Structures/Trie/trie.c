#include "trie.h"
#include <stdio.h>
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

static inline unsigned char table_to_ch(int tb){
	return tb + 61;
}

static inline int ch_to_table(unsigned char ch) {
	if (97 <= ch && ch <= 122)
		return ch - 97;
	else if (65 <= ch && ch <= 90)
		return ch - 65;
	else
		return -1;
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

	for (int i = 0; wrd[i] != 0 ; i++) {
		int c = ch_to_table(wrd[i]);
		if (tmp->chars[c] == NULL)
			tmp->chars[c] = trie_make();
		tmp = tmp->chars[c];
	}
	return tmp->terminal = true;
}

bool trie_search(Trie t_root, char *wrd) {
	Trie tmp = t_root;
	for (int i = 0;wrd[i] != 0 ; i++) {
		if (tmp->chars[wrd[i]] == NULL) 
			return false;
		tmp = tmp->chars[wrd[i]];
	}
	return tmp->terminal;
}

bool trie_delete(Trie *t_root, char *wrd) {
	Trie tmp = *t_root;
	for (int i = 0; wrd[i] != 0; i++) {
		if (tmp->chars[wrd[i]] == NULL) 
			return true;
		tmp = tmp->chars[wrd[i]];
	}
	return !(tmp->terminal = false);
}


void trie_print(Trie t_root, char* buff, int *count){
	if (t_root != NULL) {
		if (t_root->terminal == true){
			buff[++(*count)] = 0;
			printf("%s\n", buff);
			--(*count);
		}	
		for (int i = 0; i < NUM_CHARS; i++) {
			buff[*count] = table_to_ch(i);
			(*count)++;
			trie_print(t_root->chars[i], buff, count);
		}
	(*count)--;
}

