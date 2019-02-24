#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

int main(int argc, char **argv){
	int process_time = 0;	
	if(argc > 1){	
		process_time = atoi(argv[1]);
	}else{
		return 1;	
	}

	key_t svar1;
	int svarid1;
	key_t svar2;
	int svarid2;
	svar1 = ftok(".", 'x');
	svar2 = ftok(".", 'y');
	svarid1 = shmget(svar1, sizeof(int), 0666);
	svarid2 = shmget(svar2, sizeof(int), 0666);
	int *seconds = (int *)shmat(svarid1, NULL, 0);
	int *nano_seconds = (int *)shmat(svarid2, NULL, 0);
	int end_time = process_time + *nano_seconds;

	while(1){
		if(*nano_seconds > end_time){
			time_t t = time(NULL);
			char *now = ctime(&t);
			now[strlen(now) - 1] = '\0'; 
			printf("Terminated PID:%d at time %s.\n", getpid(), now);			
			break;
		}
	}
	return 0;
}
