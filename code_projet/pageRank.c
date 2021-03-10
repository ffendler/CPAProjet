#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time
#include <string.h>
#include "adjarray.h"
#include "pageRank.h"



int main(int argc,char** argv){
	adjlist* a;
	adjlist* g;
	a = readedgelist(argv[1]);
	mkadjlist(a);
	g = readedgelist(argv[1]);
	mkdirectedadjlist(g);
	unsigned long* exName = renameNodes(a,g);
	free_adjlist(a);
	//~ for(int j=50;j<atoi(argv[4]);j+=atoi(argv[5])){
		double* p = powerIteration(g,atof(argv[3]),atoi(argv[4]));
		char** top = bestnworst(p,g->n,argv[2]);
		for(int i=0;i<10;++i){
			if(i<5){
				printf("top : %s\n",top[i]);
			}
			else{
				printf("bottom : %s\n",top[i]);
			}
		//~ }
	
	
}
	free_adjlist(g);
	return 0;
}
