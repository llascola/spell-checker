#ifndef __DISTANCES__
#define __DISTANCES__

int dist_swap(char *w, int len, void* data, void func(char*,int,void*));

int dist_insert(char *w, int len, char* buff, void* data, void func(char*,int,void*));

int dist_delet(char *w, int len, void* data, void func(char*,int,void*));

int dist_remplace(char *w, int len, void* data, void func(char*,int,void*));

int dist_split(char *w1, int len, void* data, void func(char*,int,void*)); 
#endif
