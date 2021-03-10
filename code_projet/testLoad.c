#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time
#include <string.h>
#include "adjarray.h"
#include "edgelist.h"
#include "adjmatrix.h"


int main(int agc,char** argv){
	adjmatrix* m;
	adjlist* a;
	edgelist* e;
	time_t t1,t2,t3,t4;
	//~ t1=time(NULL);
	//~ m = readedgelistmatrix(argv[1]);  //Meme avec le graph amazon la matrice n*n est trop grande et le calloc renvoie NULL
	//~ mkmatrix(m);
	//~ free_adjmatrix(m);
	t2=time(NULL);
	e = readedgelist_s(argv[1]);
	free_edgelist(e);
	t3=time(NULL);
	a = readedgelist(argv[1]);
	mkadjlist(a); 
	free_adjlist(a);
	t4=time(NULL);
	
	
	
	
	//~ printf("- Matrix time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
	printf("- Edge list time = %ldh%ldm%lds\n",(t3-t2)/3600,((t3-t2)%3600)/60,((t3-t2)%60));
	printf("- Array time = %ldh%ldm%lds\n",(t4-t3)/3600,((t4-t3)%3600)/60,((t4-t3)%60));
	
	
	return 0;
}
