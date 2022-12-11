#include "dlist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

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

void dlist_destroy(DList *list, DestroyFunc destf) {
	if (!dlist_empty(*list)) {
		DNode *temp = (*list)->first;
		while (temp->next) {
			DNode *tbdest = temp;
			temp = tbdest->next;
			destf(tbdest->data);
			free(tbdest);
		}
		destf(temp->data);
		free(temp);
	}
	free(*list);
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
			visitf(list->last->data); } else if (ord == 1) {
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

void dlist_tour_ext(DList list, VisitExtFunc visitf, void* dataExt, Order ord) {
	if (!dlist_empty(list)) {
		if (ord == 0) {
			DNode *temp = list->first;
			while (temp != list->last) {
				DNode *tbdest = temp;
				temp = tbdest->next;
				visitf(tbdest->data, dataExt);
			}
			visitf(list->last->data, dataExt);
		} else if (ord == 1) {
			DNode *temp = list->last;
			while (temp != list->first) {
				DNode *tbdest = temp;
				temp = tbdest->prev;
				visitf(tbdest->data, dataExt);
			}
			visitf(list->first->data, dataExt);
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
		list->first = list->first->prev = newNode;
	} else if (ord == 1) {
		newNode->prev = list->last;
		newNode->next = NULL;
		list->last = list->last->next = newNode;
	} else {assert(0);}
	return 0;
}

void *dlist_data(DList list, unsigned int pos, CopyFunc copyf) {
	if (dlist_empty(list))
		return NULL;
	DNode* temp = list->first;
	for (unsigned int i = 0; i < pos && temp->next; temp = temp->next);
	return copyf(temp->data);
}

int dlist_delete(DList list, void* data, CompareFunc cmpf, DestroyFunc dstf) {
	if (list == NULL)
		return 1;
	if (dlist_empty(list))
		return 1;
	int flag = 0;
	DNode* tmp = list->first;
	for(;(flag = cmpf(data, tmp->data)) && tmp->next;tmp = tmp->next);
	if (flag)
		return 1;
	if (!(flag = (long)list->first->next)) 
		list->first = list->last = NULL;
	if (tmp->next) 
		tmp->next->prev = tmp->prev;
	else
		list->last = tmp->prev;
	if (flag)
		tmp->prev->next = tmp->next;
	if (tmp == list->first)
		list->first = tmp->next;
	dstf(tmp->data);
	free(tmp);
	return 0;
//	if (!flag && list->first->next) {
//		tmp->prev->next = tmp->next;
//		dstf(tmp->data);
//		free(tmp);
//		return 1;
//	} else if (!flag) {
//		dstf(tmp->data);
//		free(tmp);
//		list->first = list->last = NULL;
//		return 1;
//	} 
//	return 0;		
}

int dlist_delete_pos(DList list, unsigned int pos, DestroyFunc destf) {
	if (dlist_empty(list))
		return 1;
	DNode* temp = list->first;
	for (unsigned int i = 0; i < pos && temp->next != NULL; temp = temp->next);
	if (list->first == temp) {
		list->first = temp->next;
		list->first->prev = NULL;
	} else if (temp->next == NULL) {
		list->last = temp->prev;
		list->last->next = NULL;
	} else {
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	destf(temp->data);
	free(temp);
	return 0;
}

void* dlist_search(DList list, void* data, CompareFunc cmpf) {
	if (list == NULL)
		return NULL;
	if (dlist_empty(list))
		return NULL;
	int flag;
	DNode* tmp = list->first;
	for(;(flag = cmpf(data, tmp->data)) && tmp->next;tmp = tmp->next);
	return flag?NULL:tmp->data;
}

//int dlist_insearch(DList list, void* data, CompareFunc cmpf, CopyFunc cpyf) {
//	DNode *newNode;
//	if (dlist_empty(list)) {
//		assert((newNode = malloc(sizeof(struct _DNode))) != NULL);
//		newNode->data = cpyf(data);
//		list->first = list->last = newNode;
//		newNode->prev = newNode->next = NULL;
//		return 1;
//	} else {
//		int flag;
//		for(DNode* tmp = list->first;
//				!(flag = cmpf(data, tmp->data)) && tmp->next != NULL;
//				tmp = tmp->next);
//		if (flag) {
//			
//		}
//	} 
//	return 1;
//}

