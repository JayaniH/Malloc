#include<stdio.h>
#include<stddef.h>
#include"mymalloc.h"

struct block * base= (struct block*)memory;

void* MyMalloc(size_t bytes){
	struct block *ptr=base;
	
	if(base->size==0){ //first call of MyMalloc, initialize base
		base->size=SIZE-sizeof(struct block);
		base->free=1;
		base->next=NULL;
	}
	
	while(ptr!=NULL){
		if(ptr->size==bytes && ptr->free==1){
			ptr->free=0;
			ptr++;
			printf("Memory Allocated\n");
			return (void*)ptr;
		}
		else if(ptr->size>(bytes+sizeof(struct block)) && ptr->free==1){
			split(ptr,bytes);
			ptr++;
			printf("Memory Allocated\n");
			return (void*)ptr;
		}
		else{
			ptr=ptr->next;
		}
	}
	printf("No sufficient Memory\n");
	return NULL;
}
void split(struct block* block, size_t bytes){
	struct block *new_block=(struct block*)((char*)block+sizeof(struct block)+bytes); //create new metadata block
	new_block->free=1; //set as free
	new_block->size=block->size-bytes-sizeof(struct block);
	new_block->next=block->next;
	block->free=0; //set current block as occupied
	block->size=bytes;
	block->next=new_block;
}


void MyFree(void* block){
	if(block>(void*)memory && block<(void*)(memory+25000)){ //if the block is in range
		struct block *ptr= (struct block*)block;
		ptr--;
		ptr->free=1;
		merge(); 
		printf("Memory Freed\n");
	}
	
}

void merge(){
	struct block* ptr=base, *preptr;
	while(ptr!=NULL){
		preptr=ptr;
		ptr=ptr->next;
		if(ptr==NULL){
			break;
		}
		if(ptr->free==1 && preptr->free==1){
			while(ptr!=NULL && ptr->free==1){ //find all the adjacent free blocks
				preptr->size=preptr->size+ptr->size+sizeof(struct block);
				preptr->next=ptr->next;
				ptr=ptr->next;
			}
		}
	}
}

