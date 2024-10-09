#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct HEADER_TAG {
	struct HEADER_TAG * ptr_next; /* pointe sur le prochain bloc libre */
	size_t bloc_size; /* taille du memory bloc en octets*/
	long magic_number; /* 0x0123456789ABCDEF */
} HEADER;

void * malloc_3is(ssize_t x){
	printf("beginning : %p\n",sbrk(0));
	HEADER *head=sbrk(sizeof(HEADER)+x+sizeof(long));
	head->ptr_next=NULL;
	head->bloc_size=x;
	head->magic_number=0x0123456789ABCDEF;
	void *pointeurx=head+1;
	void *magic=sbrk(0)-sizeof(long);
	printf("beginning of x: %p\n",pointeurx);
	printf("beginning of magic number: %p\n",magic);
	printf("size of x: %li\n",magic-pointeurx);
	return pointeurx;
};

void free_3is(void *ptr){
	
	return;
};

int main(){
	void *test=malloc_3is(200);
	return 1;
}
