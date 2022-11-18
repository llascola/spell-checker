#ifndef __DISTANCES__
#define __DISTANCES__

typedef void (*VisitorFunc)(char *w, int len, void* data);

int dist_adycnt_perm(char *w, int len,VisitorFunc func, void* data);

int dist_insertion(char *w, int len,VisitorFunc func, void* data);

int dist_deletion(char *w, int len,VisitorFunc func, void* data);

int dist_remplacement(char *w, int len,VisitorFunc func, void* data);

int dist_splitting(char *w, int len,VisitorFunc func, void* data);
#endif
