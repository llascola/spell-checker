#include "dist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int dist_swap(char *w, int len, void* data, VisitFunc func) {
	char aux;
	for (int i = 0; i < len - 1; i++) {
		aux = w[i] ;
		w[i] = w[i + 1] ;
		w[i + 1] = aux;
		func(w, len, data);
		aux = w[i] ;
		w[i] = w[i + 1] ;
		w[i + 1] = aux;
	}
	return 0;
}

int dist_insert(char *w, int len, char* buff, void* data, VisitFunc func) {
	int buff_len = len + 1;
	memcpy(buff + 1, w, len);
	buff[0] = 97;
	buff[buff_len] = 0;
	for (int pos = 0; pos < buff_len; pos++) {
		for (int ch = 0; ch < 26; ch++) {
			func(buff, buff_len, data);
			buff[pos]++; 
		} 
		buff[pos] = buff[pos + 1];
		buff[pos + 1] = 97;
	} 
	return 0;
}


int dist_delet(char *w, int len, void* data, VisitFunc func) {
	char* w_del = w + 1;
	char aux;
	for (int i = 1; i < len; i++) {
		if (w[0] != w[i]) {
			func(w_del, len - 1, data);
			aux = w[0];
			w[0] = w[i];
			w[i] = aux;
		}
	}
	func(w_del, len - 1, data);
	aux = w[0];
	for (int i = 1; i < len; i++)
		w[i - 1] = w[i];
	w[len - 1] = aux;
	return 0;
}

int dist_remplace(char *w, int len, void* data, VisitFunc func) {
	char aux;
	for (int pos = 0; pos < len; pos++) {
		aux = w[pos];
		for (int i = 0; i < 26; i++) {
			if (aux != (97 + i)) {
				w[pos] = 97 + i; 
				func(w, len, data);
			}
		} 
		w[pos] = aux;
	} 
	return 0;
}

int dist_split(char *w, int len, char* buff, void* data, VisitFunc2 func) {
	int buffLen = len + 1;
	memcpy(buff + 1, w, buffLen);
	buff[buffLen] = 0;
	for (int i = 1; i < len; i++) {
		buff[i - 1] = buff[i];
		buff[i] = *" ";
		func(buff, i, len - i, data);
	}
	return 0;	
}

