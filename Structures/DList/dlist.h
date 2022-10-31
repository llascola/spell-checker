#ifndef __DLIST_H__
#define __DLIST_H__

typedef void (*DestroyFunc)(void *);
typedef void (*VisitorFunc)(void *);
typedef int (*CompareFunc)(void *data1, void *data2);
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

struct _DList{
	DNode *first;
	DNode *last;
};

typedef struct _DList* DList;

DList dlist_make();

int dlist_empty(DList list);

void dlist_destroy(DList list, DestroyFunc destf);

void dlist_tour(DList list, VisitorFunc visitf, Order ord);

int dlist_insert(DList list, void *data, CopyFunc copyf, Order ord);

void* dlist_data(DList list, unsigned int pos, CopyFunc copyf);

int dlist_delete(DList list, void* data, CompareFunc cmpf, DestroyFunc dstf);

int dlist_delete_pos(DList lista, unsigned int pos, DestroyFunc destf);

int dlist_search(DList list, void* data, CompareFunc cmpf);

int dlist_insearch(DList list, void* data, CompareFunc cmpf, CopyFunc cpyf);

#endif

