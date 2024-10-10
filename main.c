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
			void* ptrx=curr+1;
			temp->ptr_next=curr->ptr_next;

			if(x==curr->bloc_size||curr->bloc_size-x<headsize+sizeof(long)){
				curr->ptr_next=NULL;
				curr->magic_number=0x0123456789ABCDEF;
				printf("beginning of x : %p \n",ptrx);
				return ptrx;
			}

			//creation of the new bloc
			HEADER *newhead=ptrx+x+sizeof(long);
			newhead->ptr_next=NULL;
			newhead->magic_number=0x0123456789ABCDEF;
			size_t newsize=curr->bloc_size-x-headsize-sizeof(long);
			newhead->bloc_size=newsize;
			void* newptr=newhead+1;
			long* lastmn=(newptr+newsize);
			*lastmn=0x0123456789ABCDEF;
			
			free(ptrx); //sort the new bloc
			
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

void free_3is(void *ptr){ //ascending adresse order
	testoverflow(ptr);
	
	HEADER *head=ptr-headsize;
	void* headsend=ptr+head->bloc_size+sizeof(long);

	if(freeliste==NULL||head<freeliste){
		head->ptr_next=freeliste;
		if(headsend==freeliste){
			head->ptr_next=freeliste->ptr_next;
			head->bloc_size=head->bloc_size+sizeof(long)+headsize+freeliste->bloc_size;
		}
		freeliste=head;
		return;
	};
	
	HEADER *curr=freeliste;
	HEADER *temp=NULL;
	while(curr!=NULL||head>curr){
		temp=curr;
		curr=curr->ptr_next;
	};
	
	void* tempsend=ptr+temp->bloc_size+sizeof(long);

	temp->ptr_next=head;
	if(tempsend==head){
		temp->ptr_next=curr;
		temp->bloc_size=temp->bloc_size+sizeof(long)+headsize+head->bloc_size;
	}
	
	if(headsend==curr){ //we are sure that curr!=NULL
		head->ptr_next=curr->ptr_next;
		head->bloc_size=head->bloc_size+sizeof(long)+headsize+curr->bloc_size;
		return;
	}
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
