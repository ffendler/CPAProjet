#ifndef HBFS
#define HBFS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "adjarray.h"
#include "fifo.h"

int* BFS(adjlist* g,unsigned long n){
	
	time_t t1,t2;
	t1=time(NULL);
	
	fifo f = emptyFifo();
	fifo fd = emptyFifo();
	int* mark = calloc(g->n,sizeof(int));
	int* alldist = malloc(sizeof(int)*g->n);
	add(n,&f);
	add(0,&fd);
	mark[n] = 1;
	while(!isEmpty(&f)){
		unsigned long u = pop(&f);
		int d = pop(&fd);
		alldist[u] = d;

		for(int i=0;i<g->cd[u+1]-g->cd[u];i++){
			unsigned long v = g->adj[g->cd[u]+i];
			if(mark[v]==0){
				add(v,&f);
				add(d+1,&fd);
				mark[v] = 1;
			}
		}
	}
	
	t2=time(NULL);
	printf("- BFS time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
	return alldist;
}





int lower_bound(adjlist* g,int nbBFS){
	
	int* alldist;
	unsigned long n;
	int maxdist;
	do{
		srand(time(NULL));
		n = rand() % g->n;
		alldist = BFS(g,n);
		maxdist=0;
		for(unsigned long i=0;i<g->n;i++){
			if(maxdist<alldist[i]){
				maxdist = alldist[i];
				n = i;
			}
		}
	}while(maxdist == 0);
	
	for(int j=0;j<nbBFS-1;++j){
		alldist = BFS(g,n);
		maxdist=0;
		for(unsigned long i=0;i<g->n;i++){
			if(maxdist<alldist[i]){
				maxdist = alldist[i];
				n = i;
			}
		}
		
	}
	free(alldist);

	return maxdist;
}

#endif
