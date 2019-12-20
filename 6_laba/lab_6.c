#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

pthread_mutex_t mutex;
//int  *data = NULL;
int data[1024];
int size = 0;

void *writing_threadFunc(void *arg)
{
	//int writing_buf[64];
	printf("Writing thread %u\n", (unsigned int)pthread_self());
	while(1)
	{
		pthread_mutex_lock(&mutex);
		//data = (int*) malloc(sizeof(int));
		size++;
		data[size] = size;
		pthread_mutex_unlock(&mutex);

		sleep(1);
	}
	pthread_exit(0);
}


void *reading_threadFunc(void *arg)
{
	//char *read_buf = (char*) calloc (20, sizeof(char));
	//printf("Reading thread %u\n", (unsigned int)pthread_self());
	while(1)
	{
		pthread_mutex_lock(&mutex);
		printf("Reading thread %u\n", (unsigned int)pthread_self());
		int i;
		for(i = 0; i<size; i++)
		{
			printf("%d\n", data[i]);
		}
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	pthread_exit(0);
}

int main()
{
	pthread_t read[9];
	pthread_t write;
	pthread_create(&write, NULL, writing_threadFunc, NULL);
	int i;
	for(i = 0; i<9; i++)
	{
		pthread_create(&read[i], NULL, reading_threadFunc, NULL);
	}
	pthread_join(write, NULL);
	//sleep(2);
	for(i = 0; i<9; i++)
	{
		pthread_join(read[9], NULL);
	}

	pthread_mutex_destroy(&mutex);

	return 0;
}
