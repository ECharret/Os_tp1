#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct HEADER_TAG {
	struct HEADER_TAG *ptr_next;  //pointe sur le prochain bloc libre 
	size_t bloc_size; // taille du memory bloc en octets
	long magic_number;  //0x0123456789ABCDEF
} HEADER;

HEADER *freeliste=NULL;
ssize_t headsize=sizeof(HEADER);

void testoverflow(void *ptr){
	HEADER *head=ptr-headsize;
	size_t size=head->bloc_size;
	long firstmn=head->magic_number;
	long* lastmn=(ptr+size);
	if(firstmn!=0x0123456789ABCDEF||*lastmn!=0x0123456789ABCDEF){
		exit(EXIT_FAILURE);
		return;
	};
	return;
};

void *malloc_3is(size_t x){
	HEADER *curr=freeliste;
	HEADER *temp=NULL;
	while(curr!=NULL){ //reuse a bloc
		if(x<=(freeliste->bloc_size)){
			void *ptrx=freeliste+1;
			freeliste=NULL;
			printf("beginning of x : %p \n",ptrx);
			return ptrx;
		}
		if(x<=curr->bloc_size){ 
			if(x==curr->bloc_size||curr->bloc_size-x<headsize+sizeof(long)){
				void* ptrx=curr+1;
				temp->ptr_next=curr->ptr_next;
				curr->ptr_next=NULL;
				curr->magic_number=0x0123456789ABCDEF;
				printf("beginning of x : %p \n",ptrx);
				return ptrx;
			}
			void* ptrx=curr+1;
			//creation of the new bloc
			HEADER *newhead=ptrx+x+sizeof(long);
			temp->ptr_next=newhead;
			newhead->ptr_next=curr->ptr_next;
			newhead->magic_number=0x0123456789ABCDEF;
			size_t newsize=curr->bloc_size-x-headsize-sizeof(long);
			newhead->bloc_size=newsize;
			void* newptr=newhead+1;
			long* lastmn=(newptr+newsize);
			*lastmn=0x0123456789ABCDEF;
			
			//initialisation of the out bloc
			curr->bloc_size=x;
			curr->ptr_next=NULL;
			curr->magic_number=0x0123456789ABCDEF;
			printf("beginning of x : %p \n",ptrx);
			return ptrx;
		}
		temp=curr;
		curr=curr->ptr_next;
	}
	HEADER *head=sbrk(headsize+x+sizeof(long));
	head->ptr_next=NULL;
	head->bloc_size=x;
	head->magic_number=0x0123456789ABCDEF;
	void* pointeurx=head+1;
	void* magic=pointeurx+x;
	long* lastmn=(pointeurx+x);
	*lastmn=0x0123456789ABCDEF;
	printf("beginning  %p\n",pointeurx-headsize);
	printf("beginning of x %p\n",pointeurx);
	printf("beginning of magic number %p\n",magic);
	printf("size of x %li\n",magic-pointeurx);
	return pointeurx;
}

void free_3is(void *ptr){ //ascending order
	testoverflow(ptr);
	
	HEADER *head=ptr-headsize;
	

	if(freeliste==NULL||head->bloc_size<freeliste->bloc_size){
		head->ptr_next=freeliste;
		freeliste=head;
		return;
	};
	HEADER *curr=freeliste;
	HEADER *temp=NULL;
	while(head->bloc_size>curr->bloc_size){
		temp=curr;
		curr=curr->ptr_next;
	};
	temp->ptr_next=head;
	head->ptr_next=curr;
	return;
};



int main(){
	void *test=malloc_3is(300);
	free_3is(test);
	void *test2=malloc_3is(15);
	void* test3=malloc_3is(15);
	return 1;
}
