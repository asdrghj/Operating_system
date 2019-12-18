#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>


main()
{
   unlink("FIFO"); 
   int fifo = mkfifo ("FIFO", 0777);
   if(fifo < 0)
	printf("Fifo cannot be created \n");
   pid_t pid;
   switch(pid = fork())
   {
	case 0:
        {
	    int fifo_read = open("FIFO", O_RDONLY);
	    if (fifo_read == -1)
	    	printf("Fifo cannot open to read \n");
	    char *buf = (char*) calloc (200, sizeof(char));
	    read(fifo_read, buf, 5);
	    
	    //char *buf1 = (char*) calloc (10, sizeof(char));
	    //buf1 = strncpy(buf1, buf, 5);
	    //buf = strnset(buf, ' ', 5);
	    //printf("CHILD: time in parent -- %s\n", buf); 
	    printf("CHILD: parent pid  -- %s\n", buf);
	    read(fifo_read, buf, 20);
	    printf("CHILD: time in parent -- %s\n", buf); 
	    //printf("CHILD parent pid -- %20s\n", buf[24]);
	    close(fifo_read);
	    sleep(4);
	    time_t child_time = time(0);
	    printf("CHILD: time in child + 4 sec -- %s\n", ctime(&child_time));
	    
	    break;
	}

	default:
	{
	    
	    int fifo_write = open("FIFO", O_WRONLY);
	    if(fifo_write == -1)
		printf("Fifo cannot open to write \n");
	    time_t parent_time = time(0);
	    pid_t  parent_pid = getpid();
	    //printf("%d\n", getpid());
	    char *parent_pid_char;
	    char buff[20];
	    sprintf(buff, "%d", parent_pid);
	    char *time_plus_pid = strcat(buff, ctime(&parent_time));
	    //parent_pid_char = (char*)malloc(10*sizeof(char));
	    //parent_pid_char = itoa(parent_pid, buff, 20);
	    //write(fifo_write, ctime(&parent_time), sizeof(ctime(&parent_time)));
	    printf("PARENT: My pid -- %d\n", parent_pid);

	    //write(fifo_write, &parent_pid, strlen(pa));
	    write(fifo_write, &buff, strlen(buff));
	    write(fifo_write, ctime(&parent_time), 200);

	    //write(fifo_write, time_plus_pid, strlen(time_plus_pid ));

	    close(fifo_write);
	    break;
	    
       } 
    } 
   
    return 0;
}
