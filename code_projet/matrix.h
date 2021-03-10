	/*
 * matrix.h
 *
 *  Created on: 12 févr. 2021
 *      Author: Féfé
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "triangle.h"


	
double* proMat(adjlist* g,double* m,double* a){
	double* b=calloc(g->n,sizeof(double));
	unsigned long i,j,neighbors,x;
	
	x=g->n;
	//~ for(unsigned long i=0;i<g->n;++i){
		//~ b[i] = 1.0 / x;
	//~ }
	for(unsigned long i=0;i<g->n;++i){
		for(unsigned long j=0;j<g->cd[i+1]-g->cd[i];++j){
			b[i] += m[g->cd[i]+j] * a[j];
		}
		
	}
	return b;
}





double* createTransMat(adjlist* m){
	double* t=malloc(m->e*sizeof(double));
	for(unsigned long i=0;i<m->n;++i){
		for(unsigned long j=0;j<m->cd[i+1]-m->cd[i];++j){
			t[m->cd[i]+j] = 1.0 / (m->cd[i+1]-m->cd[i]);
		}
		
	}
		
	
	return t;
}



#endif /* MATRIX_H_ */
