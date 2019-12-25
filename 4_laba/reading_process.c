#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define shmem_file "shared_memory_file"

int main()
{
	key_t key = ftok(shmem_file, 14);
	int shmid = shmget(key, 50, 0666);
	if(shmid == -1)
	{
		printf("Shared memoty cannot be created \n");
		return 0;
	}

	char *addr = shmat(shmid, NULL, 0);
	if (addr == (char*)-1)
	{
		printf("Shmat error\n");
		return 0;
	}

	printf("Host process: :%d, %d\n", key, shmid);

	while(1)
	{
		printf("%s", addr);
		sleep(1);
	}
	
	//printf("Host process: :%d, %d\n", key, shmid);

	return 0;
}
