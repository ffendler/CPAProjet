/*
 * triangle.h
 *
 *  Created on: 5 févr. 2021
 *      Author: Féfé
 */



#ifndef TRIANGLE_H_
#define TRIANGLE_H_



#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "adjarray.h"
#define TSIZE 100000




typedef struct{
	edge e1;
	edge e2;
	edge e3;
}triangle;

unsigned long intersect(unsigned long* l1,unsigned long legthL1 , unsigned long* l2, unsigned long legthL2){
	unsigned long n,i,j;
	i = j = 0;
	n = 0;
	while(i<legthL1 && j<legthL2){
		while(i<legthL1 && j<legthL2){
			if(l1[i] == l2[j]){
				++n;
				++i;
				++j;
			}
			else if(l1[i] < l2[j]){
				++i;
			}
			else{
				++j;
			}
		}
	}
	return n;
}


void sort(unsigned long* tab,unsigned long t){
	unsigned long i,j,tmp;
	for (i=0 ; i < t-1; i++)
	{
		//~ printf("2\n");
		for (j=0 ; j < t-i-1; j++)
		{

		  if (tab[j] > tab[j+1]) 
		  {
			tmp = tab[j];
			tab[j] = tab[j+1];
			tab[j+1] = tmp;
		  }

		}

	}


}

unsigned long nbTriangles(adjlist* a){
	time_t t1,t2;
	t1=time(NULL);
	unsigned long nbTri,i,j,neighbors,k,s,t;
	nbTri=0;
	
	unsigned long** temp;
	temp = malloc(a->n * sizeof(unsigned long));
	unsigned long* newNeigh = malloc(a->n * sizeof(unsigned long)); 
	
	
	for(i=0;i<a->n;i++){
		neighbors = a->cd[i+1]-a->cd[i];
		k = 0;
		temp[i] = malloc(neighbors * sizeof(unsigned long));
		for(j=0;j<neighbors;j++){
			if(i<a->adj[a->cd[i]+j]){
				temp[i][k] = a->adj[a->cd[i] + j];
				k++;
			}
		}
		newNeigh[i] = k;
		if(newNeigh[i]>0){
			sort(temp[i],newNeigh[i]);
		}
	}
	

	

	for(i=0;i<a->e;++i){
		s = a->edges[i].s;
		t = a->edges[i].t;
		nbTri = intersect(temp[s] , newNeigh[s] , temp[t], newNeigh[t]) + nbTri;
	}
	t2=time(NULL);
	printf("- Triangle time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
	return nbTri;
}









#endif /* TRIANGLE_H_ */
