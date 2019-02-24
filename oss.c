#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void read_args(int argc, char **argv,int *h, int *n, int *s, char **i, char **o){
	int j = 0;
	for(j = 0 ; j < argc ; ++j){
		if(strcmp(argv[j], "-h") == 0){
			*h = atoi(argv[j + 1]);
		}
		if(strcmp(argv[j], "-n") == 0){
			*n = atoi(argv[j + 1]);
		}
		if(strcmp(argv[j], "-s") == 0){
			*s = atoi(argv[j + 1]);
		}		
		if(strcmp(argv[j], "-i") == 0){
			*i = argv[j + 1];
		}
		if(strcmp(argv[j], "-o") == 0){
			*o = argv[j + 1];
		}
	}
}

int main(int argc, char **argv){
	int h = 1;	
	int n = 4;
	int s = 2;
	char *i = "input.txt";
	char *o = "output.txt";
	key_t svar1;
	int svarid1;
	key_t svar2;
	int svarid2;
	svar1 = ftok(".", 'x');
	svar2 = ftok(".", 'y');
	svarid1 = shmget(svar1, sizeof(int), IPC_CREAT | 0666);
	svarid2 = shmget(svar2, sizeof(int), IPC_CREAT | 0666);
	read_args(argc, argv, &h, &n, &s, &i, &o);
	int *seconds = (int *)shmat(svarid1, NULL, 0);
	int *nano_seconds = (int *)shmat(svarid2, NULL, 0);
	*seconds = 0;
	*nano_seconds = 0;
	int increment = 20;
	int pids[n];
	int j =0;
	for (j = 0 ; j < n ; j++){
		pids[j] = fork();
		if(pids[j] == 0){
			char *const paramList[] = {"./user", "2000", NULL};
			int r= execv("./user", paramList);
		}
	}

	int stat;
	while(1){
		int done = 1;
		for(j = 0 ; j < n ; j++){
			done = done * waitpid(pids[j] , &stat, WNOHANG);
		}
		if(done != 0){
			break;
		}else{
			*nano_seconds = *nano_seconds + increment;
		}
	}
}
