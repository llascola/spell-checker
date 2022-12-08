#ifndef __DISTANCES__
#define __DISTANCES__

typedef void (*VisitFunc)(char* w, int len, void* data);
typedef void (*VisitFunc2)(char* w, int len1, int len2, void* data);

int dist_swap(char *w, int len, void* data, VisitFunc func);

int dist_insert(char *w, int len, char* buff, void* data, VisitFunc func);

int dist_delet(char *w, int len, void* data,VisitFunc func);

int dist_remplace(char *w, int len, void* data, VisitFunc func);

int dist_split(char *w, int len, char* buff, void* data, VisitFunc2 func); 

#endif
