#include "segdef.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


segment * initialisation(int semid,int shmid){
	if ((semid=semget(cle,0,0))==-1) {
		perror("semget");
		exit(1); 
	}
	printf("%s%d","Id semaphore recupere=\n",semid);
	if ((shmid=shmget(cle,0,0))==-1){
		perror("shmget");
		exit(1);
	}
	printf("%s%d\n","L'identifiant memoire est ",shmid);
	segment *buf;
	if ((buf=shmat(shmid,0,0))== NULL) {
		perror("shmat");
		exit(1); }
	init_rand();
	return buf;
}

void clientprocess(){
	int semid=semget(cle,0,0);
	int shmid=shmget(cle,0,0);
	segment *seg=initialisation(semid,shmid);
	int nbrrequest=0;
	while(nbrrequest<100){
		acq_sem(semid,seg_dispo);
		
		//printf("step 2");
		seg->pid=getpid();
		seg->req=nbrrequest;
		long myresult=0;
		for(int i=0; i<maxval;i++){
			seg->tab[i]=getrand();
			myresult=myresult+seg->tab[i];
		}
		myresult=myresult/maxval;
		//printf("intern res =%ld\n",myresult);
		acq_sem(semid,seg_init);
		
		//printf("step 3");
		wait_sem(semid,res_ok);
		
		//printf("step 4");
		long servres=seg->result;
		lib_sem(semid,seg_init);
		
		//printf("step 5");
		acq_sem(semid,res_ok);
		lib_sem(semid,res_ok);
		
		//printf("step 6");
		lib_sem(semid,seg_dispo);
		
		//printf("step 7");
		if(servres==myresult){
			//printf("same result\n");
		}
		else{
			printf("not the same result\n");
			exit(EXIT_FAILURE);
		}
		nbrrequest++;
	}
	shmdt(seg);
	printf("yaaaaaay");
	exit(EXIT_SUCCESS);
}

int main(){
	const int N = 12;
	pid_t pid;
	
	for (int i = 0; i < N; i++) {
		pid = fork ();
		
		if (pid < 0){
			perror ("Échec de fork");
			exit(EXIT_FAILURE);
		}
		else if(pid==0){
			clientprocess();
		exit(0);
	}
	}
	
	for (int i = 0; i<N; i++) {
		wait (NULL);
	}
	return 0;
}
