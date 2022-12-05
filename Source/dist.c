#include "dist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Word dist_word_make(char *w, int len){
	Word new_word = malloc(sizeof(struct _Word));
	new_word->word = malloc(len + 1);
	memcpy(new_word->word, w, len + 1);
	new_word->len = len;
	return new_word;
}

void dist_word_dest(Word *distWord){
	free((*distWord)->word);
	free((*distWord));
}

int dist_word_compare(Word distWord1, Word distWord2) {
	if (distWord1->len != distWord2->len)
		return -1;
	return strcmp(distWord1->word, distWord2->word);
}

int dist_hstb_size(int len) {
	return (len*28)*2 ;
}

unsigned dist_word_hash(Word distWord){
	return hash_len(distWord->word, distWord->len);
}

void* id(void* data){
	return data;
}

CHash dist_hstb_make() {
	CHash distHstb = chash_make(INIT_HSTB_SIZE,
															id,
															(DestroyFunc) dist_word_dest,
															(CompareFunc) dist_word_compare,
															(HashFunc) dist_word_hash); 
	return distHstb;
}

int dist_adycnt_perm(char *w, int len) {
	char aux;
	for (int i = 0; i < len - 1; i++) {
		aux = w[i] ;
		w[i] = w[i + 1] ;
		w[i + 1] = aux;
//		func(w, len, data);
		aux = w[i] ;
		w[i] = w[i + 1] ;
		w[i + 1] = aux;
	}
	return 0;
}

int dist_insertion(char *w, int len, char* buff) {
	int buff_len = len + 1;
	memcpy(buff + 1, w, len);
	buff[0] = 97;
	for (int pos = 0; pos < buff_len; pos++) {
		for (int ch = 0; ch < 26; ch++) {
//			func(buff, buff_len, data);
			buff[pos]++; 
		} 
		buff[pos] = buff[pos + 1];
		buff[pos + 1] = 97;
	} 
	return 0;
}


int dist_deletion(char *w, int len) {
	char* w_del = w + 1;
	char aux;
	for (int i = 1; i < len; i++) {
		if (w[0] != w[i]) {
//			func(w_del, len - 1, data);
			aux = w[0];
			w[0] = w[i];
			w[i] = aux;
		}
	}
//	func(w_del, len - 1, data);
	aux = w[0];
	for (int i = 1; i < len; i++)
		w[i - 1] = w[i];
	w[len - 1] = aux;
	return 0;
}



int dist_remplacement(char *w, int len) {
	char aux;
	for (int pos = 0; pos < len; pos++) {
		aux = w[pos];
		for (int i = 0; i < 26; i++) {
			if (aux != (97 + i)) {
				w[pos] = 97 + i; 
//				func(w, len, data);
			}
		} 
		w[pos] = aux;
	} 
	return 0;
}


int dist_splitting(char *w1, int len) {
	char* w2 = w1 + 1;
	int len1 = 1;
	int len2 = len - 1;
	for (int i = 0; i < len - 1; i++) {
//		func(w1, len1, data);
//		func(w2, len2, data);
		len1 += 1;
		len2 -= 1;
		w2 += 1;
	}
	return 0;	
}







