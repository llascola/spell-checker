#ifndef __TRIE_H__
#define __TRIE_H__
#define NUM_CHARS 26
#include <stdbool.h>

struct _TNode {
	struct _TNode *chars[NUM_CHARS];
	bool terminal;
	char** suggestions;
	int n_sugg;
};

typedef struct _TNode *Trie;

Trie trie_make();

void trie_destroy(Trie t);

bool trie_insert(Trie *t, char *wrd, int len, char** suggestions, int n_sugg);

char** trie_search(Trie t, char *wrd, int len);

bool trie_delete(Trie *t, char *wrd, int len);

void trie_print_1(Trie t_root, char* buff, int *count);

void trie_print(Trie t_root, char* buff);
#endif
