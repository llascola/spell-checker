#ifndef __TRIE_H__
#define __TRIE_H__
#define NUM_CHARS 26

struct _TNode {
	struct _TNode *chars[NUM_CHARS];
	char terminal;
};

typedef struct _TNode *Trie;

Trie trie_make();

void trie_destroy(Trie t);

int trie_insert(Trie *t, char *wrd, int len, char cache_status);

int trie_search(Trie t, char *wrd, int len);

int trie_delete(Trie *t, char *wrd, int len);

void trie_print(Trie t_root, char* buff);
#endif
