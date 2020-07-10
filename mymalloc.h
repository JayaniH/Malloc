#include<stdio.h>
#include<stddef.h>
#define SIZE 25000

struct block{
	size_t size;
	int free;
	struct block * next;
};

char memory[SIZE];
 
 //struct block * base= (struct block*)memory;
 
 void * MyMalloc(size_t bytes);
 void split(struct block* block, size_t bytes);
 void MyFree(void * block);
 void merge();
