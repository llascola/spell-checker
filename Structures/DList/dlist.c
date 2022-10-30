#include "dlist.h"
#include <assert.h>
#include <stdlib.h>

DList dlist_make() {
	DList newList;
	newList.first = NULL;
	newList.last  = NULL;
	return newList;
}

int dlist_empty(DList list) {
	return list.first == NULL;
}

void dlist_destroy(DList list, DestroyFunc destf) {
	if (!dlist_empty(list)) {
		DNode *temp = list.first;
		while (temp != list.last) {
			DNode *tbdest = temp;
			temp = tbdest->next;
			destf(tbdest->data);
			free(tbdest);
		}
		destf(list.last->data);
		free(list.last);
	}
}

void dlist_tour(DList list, VisitorFunc visitf, Order ord) {
	if (!dlist_empty(list)) {
		if (ord == 0) {
			DNode *temp = list.first;
			while (temp != list.last) {
				DNode *tbdest = temp;
				temp = tbdest->next;
				visitf(tbdest->data);
			}
			visitf(list.last->data);
		} else if (ord == 1) {
			DNode *temp = list.last;
			while (temp != list.first) {
				DNode *tbdest = temp;
				temp = tbdest->prev;
				visitf(tbdest->data);
			}
			visitf(list.first->data);
		} else {assert(0);} 
	}
}

DList dlist_insert(DList list, void *data, CopyFunc copyf, Order ord) {
	DNode *newNode;
	assert((newNode = malloc(sizeof(struct _DNode))) != NULL);
	newNode->data = copyf(data);
	if (dlist_empty(list)) {
		list.first = list.last = newNode;
		newNode->prev = newNode->next = NULL;
	} else if (ord == 0) {
		newNode->prev = NULL;
		newNode->next = list.first;
		list.first = newNode;
	} else if (ord == 1) {
		newNode->prev = list.last;
		newNode->next = NULL;
		list.last = newNode;
	} else {assert(0);}
	return list;
}

void *dlist_data(DList list, unsigned int pos, CopyFunc copyf) {
	if (dlist_empty(list))
		return NULL;
	DNode* temp = list.first;
	for (int i = 0; i < pos && temp->next != NULL; temp = temp->next);
	return copyf(temp->data);
}

DList dlist_delete(DList list, unsigned int pos, DestroyFunc destf) {
	if (dlist_empty(list))
		return list;
	DNode* temp = list.first;
	for (int i = 0; i < pos && temp->next != NULL; temp = temp->next);
	if (temp->next == NULL){
		list.last = temp->prev;
		list.last->next = NULL;
	} else 
		temp->prev->next = temp->next;
	destf(temp->data);
	free(temp);
	return list;
}













	
