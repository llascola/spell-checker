#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Distances/dist.h"

void my_printf(char* w, __attribute__((unused)) int len,__attribute__((unused)) void* data){
	printf("%s\n", w);
}

void my_printf2(char* w, int len, __attribute__((unused))void* data){
	for(int i = 0; i < len; i++)
		putchar(w[i]);
	putchar(10);
}

int main(){
	char a[9] = "holamijo";
	char buff[100];
	puts("Adjacent->>");
	dist_adycnt_perm(a, 8, (VisitorFunc) my_printf2,(void*) a );
	puts("Insertions->>");
	dist_insertion(a, 8, buff, (VisitorFunc) my_printf2,(void*) a );
	puts("deletions->>");
	dist_deletion(a, 8, (VisitorFunc) my_printf2,(void*) a );
	puts("remplacement->>");
	dist_remplacement(a, 8, (VisitorFunc) my_printf2,(void*) a );
	puts("splitting->>");
	dist_splitting(a, 8, (VisitorFunc) my_printf2,(void*) a );
	return 0;
}
