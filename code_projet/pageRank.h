#ifndef PAGERANK_H_
#define PAGERANK_H_

#include "matrix.h"
#include "adjmatrix.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void normalize(double* p,unsigned long n){
	double p1 = 0;
	for(unsigned long i=0;i<n;++i){
		p1 += p[i];
	}
	for(unsigned long i=0;i<n;++i){
		p[i] += (1 - p1)/n;
	}
	
}

double* powerIteration(adjlist* g,float alpha,int ite){
	time_t t1,t2;
	t1=time(NULL);
	double* t = createTransMat(g);
	double* l = malloc(g->n*sizeof(double));
	double* p = malloc(g->n*sizeof(double));
	double x = 1.0/g->n;
	for(unsigned long i=0;i<g->n;++i){
		p[i] = x*x;
	}
	for(int i=0;i<ite;++i){
		p = proMat(g,t,p);
		for(unsigned long j=0;j<g->n;++j){
			p[j]=(1-alpha) * p[j] + alpha*x;
		}
		normalize(p,g->n);
	}
	t2=time(NULL);

	printf("- Pagerank time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
	free(l);
	free(t);
	return p;
}




char** bestnworst(double* p,unsigned long n, char* input){
	FILE *file=fopen(input,"r");
	char buffer[1000];
	unsigned long intbuf;
	double bestNworst[10];
	unsigned long id_bestNworst[10];
	char** cat;
	char** output;
	
	for(int i=0;i<10;++i){
		bestNworst[i] = p[0];
		id_bestNworst[i] = 0;
	}
	for(unsigned long i =1;i<n;++i){
		if(p[i]>bestNworst[0]){
			bestNworst[0] = p[i];
			id_bestNworst[0] = i;
		}
		else if(p[i]>bestNworst[1]){
			bestNworst[1] = p[i];
			id_bestNworst[1] = i;
		}
		else if(p[i]>bestNworst[2]){
			bestNworst[2] = p[i];
			id_bestNworst[2] = i;
		}
		else if(p[i]>bestNworst[3]){
			bestNworst[3] = p[i];
			id_bestNworst[3] = i;
		}
		else if(p[i]>bestNworst[4]){
			bestNworst[4] = p[i];
			id_bestNworst[4] = i;
		}
		
		if(p[i]<bestNworst[9]){
			bestNworst[9] = p[i];
			id_bestNworst[9] = i;
		}
		else if(p[i]<bestNworst[8]){
			bestNworst[8] = p[i];
			id_bestNworst[8] = i;
		}
		else if(p[i]<bestNworst[7]){
			bestNworst[7] = p[i];
			id_bestNworst[7] = i;
		}
		else if(p[i]<bestNworst[6]){
			bestNworst[6] = p[i];
			id_bestNworst[6] = i;
		}
		else if(p[i]<bestNworst[5]){
			bestNworst[5] = p[i];
			id_bestNworst[5] = i;
		}	
	}
	
	cat = malloc(n*sizeof(int));
	unsigned long j = 0;
	
	char buf;
	while (fscanf(file,"%lu", &intbuf)==1) {
		//~ printf("%s\n",buffer);
		buf = fgetc(file);
		buf = fgetc(file);
		int i = 0;
		while(buf!='\n'){
			buffer[i]=buf;
			buf = fgetc(file);
			i++;
		}
		buffer[i] = '\0';
		cat[j] = malloc((strlen(buffer)+1)*sizeof(char));
		strcpy(cat[j],buffer);
		j++;
	}
	
		
		
	output = malloc(10*sizeof(long));
	for(int i = 0;i<10;++i){
		
		output[i] = malloc(strlen(cat[id_bestNworst[i]]));
		strcpy(output[i],cat[id_bestNworst[i]]);
		

		
	}
	
	return output;
}	




#endif
