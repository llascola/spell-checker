#ifndef __TRIE_H__
#define __TRIE_H__
#define NUM_CHARS 26
#include <stdbool.h>

struct _TNode {
	struct _TNode *chars[NUM_CHARS];
	bool terminal;
};

typedef struct _TNode *Trie;

Trie trie_make();

void trie_destroy(Trie t);

bool trie_insert(Trie *t, char *wrd);

bool trie_search(Trie t, char *wrd);

bool trie_delete(Trie *t, char *wrd);
#endif
