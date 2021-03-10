#include <stdlib.h>
#include <stdio.h>

typedef struct elem{
	unsigned long n;
	struct elem* next;
}elem;


typedef struct {
	unsigned long size;
	elem* head;
	elem* tail;
}fifo;

int isEmpty(fifo* f){
	return f->size==0;
}

unsigned long pop(fifo* f){
	if(isEmpty(f)){
		printf("FIFO is empty\n");
		return -1;
	}
	unsigned long tmp = f->head->n;
	f->head=f->head->next;
	--f->size;
	return tmp;
}

void add(unsigned long n,fifo* f){
	elem* e = malloc(sizeof(elem));
	e->n = n;
	e->next = NULL;
	if(isEmpty(f)){
		f->head = e;
		f->tail = e;
	}
	else{
		f->tail->next = e;
		f->tail = e;

	}
	++f->size;
}

void print_fifo(fifo f){
	printf("[");
	unsigned long tmp = f.size-1;
	for(int i=0;i<tmp;++i){
		printf("%lu,",pop(&f));
	}
	printf("%lu]\n",pop(&f));
}

fifo emptyFifo() {
	fifo f;
	f.size = 0;
	f.head = f.tail = NULL;
	return(f);
}


