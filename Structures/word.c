#include "word.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Word word_make(char *w, int len){
	Word new_word = malloc(sizeof(struct _Word));
	new_word->word = malloc(len + 1);
	memcpy(new_word->word, w, len);
	new_word->word[len] = 0;
	new_word->len = len;
	return new_word;
}

char* word_string(Word word){return word->word;}

int word_len(Word word){return word->len;}

void word_dest(Word distWord){
	free(distWord->word);
}

int word_compare(Word distWord1, Word distWord2) {
	if (distWord1->len != distWord2->len)
		return -1;
	return strcmp(distWord1->word, distWord2->word);
}

void word_visit(Word word, void* data, void func(char*,int,void*)){
	func(word->word, word->len, data);
}

