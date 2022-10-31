#include "dlist.h"
#include <assert.h>
#include <stdlib.h>

DList dlist_make() {
	DList newList;
	assert((newList = malloc(sizeof(struct _DList))));
	newList->first = NULL;
	newList->last  = NULL;
	return newList;
}

int dlist_empty(DList list) {
	return list->first == NULL;
}

void dlist_destroy(DList list, DestroyFunc destf) {
	if (!dlist_empty(list)) {
		DNode *temp = list->first;
		while (temp != list->last) {
			DNode *tbdest = temp;
			temp = tbdest->next;
			destf(tbdest->data);
			free(tbdest);
		}
		destf(list->last->data);
		free(list->last);
	}
}

void dlist_tour(DList list, VisitorFunc visitf, Order ord) {
	if (!dlist_empty(list)) {
		if (ord == 0) {
			DNode *temp = list->first;
			while (temp != list->last) {
				DNode *tbdest = temp;
				temp = tbdest->next;
				visitf(tbdest->data);
			}
			visitf(list->last->data);
		} else if (ord == 1) {
			DNode *temp = list->last;
			while (temp != list->first) {
				DNode *tbdest = temp;
				temp = tbdest->prev;
				visitf(tbdest->data);
			}
			visitf(list->first->data);
		} else {assert(0);} 
	}
}

int dlist_insert(DList list, void *data, CopyFunc copyf, Order ord) {
	DNode *newNode;
	assert((newNode = malloc(sizeof(struct _DNode))) != NULL);
	newNode->data = copyf(data);
	if (dlist_empty(list)) {
		list->first = list->last = newNode;
		newNode->prev = newNode->next = NULL;
	} else if (ord == 0) {
		newNode->prev = NULL;
		newNode->next = list->first;
		list->first = newNode;
	} else if (ord == 1) {
		newNode->prev = list->last;
		newNode->next = NULL;
		list->last = newNode;
	} else {assert(0);}
	return 1;
}

void *dlist_data(DList list, unsigned int pos, CopyFunc copyf) {
	if (dlist_empty(list))
		return NULL;
	DNode* temp = list->first;
	for (int i = 0; i < pos && temp->next != NULL; temp = temp->next);
	return copyf(temp->data);
}

int dlist_delete(DList list, void* data, CompareFunc cmpf, DestroyFunc dstf) {
	if (dlist_empty(list))
		return 0;
	int flag;
	DNode* tmp = list->first;
	for(;
			!(flag = cmpf(data, tmp->data)) && tmp->next != NULL;
			tmp = tmp->next);
	if (flag) {
		tmp->prev->next = tmp->next;
		dstf(tmp->data);
		free(tmp);
		return 1;
	} else 
		return 0;
}

int dlist_delete_pos(DList list, unsigned int pos, DestroyFunc destf) {
	if (dlist_empty(list))
		return 1;
	DNode* temp = list->first;
	for (int i = 0; i < pos && temp->next != NULL; temp = temp->next);
	if (temp->next == NULL){
		list->last = temp->prev;
		list->last->next = NULL;
	} else 
		temp->prev->next = temp->next;
	destf(temp->data);
	free(temp);
	return 1;
}

int dlist_search(DList list, void* data, CompareFunc cmpf) {
	if (dlist_empty(list))
		return 0;
	int flag;
	for(DNode* tmp = list->first;
			!(flag = cmpf(data, tmp->data)) && tmp->next != NULL;
			tmp = tmp->next);
	return flag;
}

