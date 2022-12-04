#include "dist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int dist_adycnt_perm(char *w, int len, VisitorFunc func, void* data) {
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

int dist_insertion(char *w, int len, char* buff, VisitorFunc func, void* data) {
	int buff_len = len + 1;
	memcpy(buff + 1, w, len);
	buff[0] = 97;
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


int dist_deletion(char *w, int len, VisitorFunc func, void* data) {
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



int dist_remplacement(char *w, int len, VisitorFunc func, void* data) {
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


int dist_splitting(char *w1, int len, VisitorFunc func, void* data) {
	char* w2 = w1 + 1;
	int len1 = 1;
	int len2 = len - 1;
	for (int i = 0; i < len - 1; i++) {
		func(w1, len1, data);
		func(w2, len2, data);
		len1 += 1;
		len2 -= 1;
		w2 += 1;
	}
	return 0;	
}







