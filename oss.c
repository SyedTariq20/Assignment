#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

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
	int *svarptr1 = (int *)shmat(svarid1, NULL, 0);
	int *svarptr2 = (int *)shmat(svarid2, NULL, 0);
	*svarptr1 = 0;
	*svarptr1 = 0;
}
