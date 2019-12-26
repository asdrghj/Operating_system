#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define FIFO_FILE "FIFO"

main()
{
	unlink(FIFO_FILE); 
	int fifo = mkfifo (FIFO_FILE, 0777);
	if(fifo < 0)
	{
		printf("Fifo cannot be created \n");
		return 0;
	}
	pid_t pid;
	switch(pid = fork())
	{
		case 0:
		{
			int fifo_read = open(FIFO_FILE, O_RDONLY);
			if (fifo_read == -1)
			{
				printf("Fifo cannot open to read \n");
				return 0;
			}
			char buf[25];
			read(fifo_read, buf, 5);
			printf("CHILD: Parent pid  -- %s\n", buf);
			read(fifo_read, buf, 25);
			printf("CHILD: Time in parent -- %s\n", buf); 
			close(fifo_read);
			sleep(2);
			time_t child_time = time(0);
			printf("CHILD: My time + 2 sec -- %s\n", ctime(&child_time));
			break;
		}
		default:
		{ 
			int fifo_write = open(FIFO_FILE, O_WRONLY);
			if(fifo_write == -1)
			{
				printf("Fifo cannot open to write \n");
				return 0;
			}
			time_t parent_time = time(0);
			pid_t  parent_pid = getpid();
			char buff[25];
			sprintf(buff, "%d", parent_pid);
			printf("PARENT: My pid -- %d\n", parent_pid);
			printf("PARENT: My time -- %s\n", ctime(&parent_time));
			write(fifo_write, &buff, strlen(buff));
			write(fifo_write, ctime(&parent_time), 50);
			close(fifo_write);
			break; 
		} 
	} 
	return 0;
}
