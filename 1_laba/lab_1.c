#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void atex_func()
{
	printf("Вызов atexit() \n");
}

main()
{
    pid_t pid;
    int rv;
    switch(pid = fork())
    {
	case -1: perror("fork");
	    exit(1);

	case 0:
		atexit(atex_func);
	    printf("Child: Это процесс потомок\n");
	    printf("Child: Мой PID --%d\n", getpid());
	    printf("Child: PID моего родителя --%d\n", getppid());
	    printf("Child: Введите мой код возврата:");
	    scanf("%d", &rv);
	    printf("Child: Выход!\n");
	    exit(rv);
	default:
		atexit(atex_func);
	    printf("Parent: Parent: Это процесс родитель\n");
	    printf("Parent: Мой PID --%d\n", getpid());
	    printf("Parent: PID моего потомка --%d\n", pid);
	    printf("Parent: Жду, пока потомок не вызовет exit... \n");
	    wait(NULL);
	    printf("Parent: Код возврата потомка:%d\n", WEXITSTATUS(rv));
	    printf("Parent: Выход!\n");
    }
	return 0;
}

