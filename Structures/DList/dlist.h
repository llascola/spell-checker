#ifndef __DLIST_H__
#define __DLIST_H__

typedef void (*DestroyFunc)(void *);
typedef void (*VisitorFunc)(void *);
typedef void *(*CopyFunc)(void *);

typedef enum {
	FORWARD,
	BACKWARD
} Order;

typedef struct _DNode {
	void *data;
	struct _DNode *next;
	struct _DNode *prev;
} DNode;

typedef struct {
	DNode *first;
	DNode *last;
} DList;

DList dlist_make();

int dlist_empty(DList list);

void dlist_destroy(DList list, DestroyFunc destf);

void dlist_tour(DList list, VisitorFunc visitf, Order ord);

DList dlist_insert(DList list, void *data, CopyFunc copyf, Order ord);

void* dlist_data(DList list, unsigned int pos, CopyFunc copyf);

DList dlist_delete(DList lista, unsigned int pos, DestroyFunc destf);

#endif

