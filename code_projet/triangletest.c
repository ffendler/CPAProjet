#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "adjarray.h"
#include "triangle.h"



int main(int argc,char** argv){

	adjlist* a;
	a = readedgelist(argv[1]);
	mkadjlist(a);
	printf("nb triangles : %lu\n",nbTriangles(a));
	return 0;
}

