#ifndef __WORD__
#define __WORD__

struct _Word{
	char* word;
	int len;
};

typedef struct _Word* Word;

Word word_make(char *w, int len);

void word_dest(Word *distWord);

int word_compare(Word distWord1, Word distWord2);

char* word_string(Word word);

int word_len(Word word);

void word_visit(Word word, void* data, void func(char*,int,void*));

#endif
