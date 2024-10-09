#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct HEADER_TAG {
	struct HEADER_TAG * ptr_next; /* pointe sur le prochain bloc libre */
	size_t bloc_size; /* taille du memory bloc en octets*/
	long magic_number; /* 0x0123456789ABCDEFL*/
} HEADER;

HEADER *freeliste=NULL;

void * malloc_3is(ssize_t x){
	HEADER *head=sbrk(sizeof(HEADER)+x+sizeof(long));
	head->ptr_next=NULL;
	head->bloc_size=x;
	head->magic_number=0x0123456789ABCDEFL;
	void *pointeurx=head+1;
	void *magic=sbrk(0)-sizeof(long);
	printf("beginning : %p\n",pointeurx-sizeof(HEADER));
	printf("beginning of x: %p\n",pointeurx);
	printf("beginning of magic number: %p\n",magic);
	printf("size of x: %li\n",magic-pointeurx);
	return pointeurx;
};

void free_3is(void *ptr){
	HEADER *head=ptr-sizeof(HEADER);
	head->ptr_next=freeliste;
	freeliste=head;
	printf("freeliste: %p \n",freeliste);
	return;
};

int main(){
	void *test=malloc_3is(200);
	free_3is(test);
	return 1;
}

int main(){
	void *test=malloc_3is(200);
	return 1;
}
