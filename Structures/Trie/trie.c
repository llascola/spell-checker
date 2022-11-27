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

//static inline unsigned char table_to_ch(int tb){
//	return tb + 97;
//}

//static inline int ch_to_table(unsigned char ch) {
//	if (97 <= ch && ch <= 122)
//		return ch - 97;
//	else if (65 <= ch && ch <= 90)
//		return ch - 65;
//	else
//		return -1;
//}
void trie_destroy(Trie t){
	if (t != NULL) {
		for(int i = 0; i < NUM_CHARS; i++) 
				trie_destroy(t->chars[i]);
	free(t);
	}
}

bool trie_insert(Trie *t_root, char *wrd, int len) {
	if (*t_root == NULL) 
		*t_root = trie_make();

	Trie tmp = *t_root;

	for (int i = 0; i < len ; i++) {
		int c = (unsigned char)wrd[i] - 97;
		if (tmp->chars[c] == NULL)
			tmp->chars[c] = trie_make();
		tmp = tmp->chars[c];
	}
	return tmp->terminal = true;
}

bool trie_search(Trie t_root, char *wrd, int len) {
	Trie tmp = t_root;
	for (int i = 0; i < len; i++) {
		int c = (unsigned char)wrd[i] - 97;
		if (tmp->chars[c] == NULL) 
			return false;
		tmp = tmp->chars[c];
	}
	return tmp->terminal;
}

bool trie_delete(Trie *t_root, char *wrd, int len) {
	Trie tmp = *t_root;
	for (int i = 0; i < len; i++) {
		int c = (unsigned char)wrd[i] - 97;
		if (tmp->chars[c] == NULL) 
			return true;
		tmp = tmp->chars[c];
	}
	return !(tmp->terminal = false);
}


void trie_print_1(Trie t_root, char* buff, int *count){
	if (t_root != NULL) {
		if (t_root->terminal == true){
			buff[++(*count)] = 0;
			printf("%s\n", buff);
			--(*count);
		}	
		for (int i = 0; i < NUM_CHARS; i++) {
			buff[*count] = i + 97;
			(*count)++;
			trie_print_1(t_root->chars[i], buff, count);
		}
	(*count)--;
}	else
		(*count)--;
}

void trie_print(Trie t_root, char* buff){
	int count = 0;
	trie_print_1(t_root, buff, &count);
}

