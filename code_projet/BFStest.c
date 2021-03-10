#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time
#include <string.h>
#include "adjarray.h"
#include "BFS.h"



int main(int argc,char** argv){
	time_t t1,t2;
	t1=time(NULL);

	adjlist* a;
	a = readedgelist(argv[1]);
	mkadjlist(a);
	int* allDist = BFS(a,0);
	
	int lowbound;
	t1=time(NULL);
	lowbound = lower_bound(a,atoi(argv[2]));
	t2=time(NULL);

	
	printf("lower bound : %d\n",lowbound);
	printf("- Lower bound time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
	free_adjlist(a)
	return 0;
}
