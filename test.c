#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	callexecve(void)
{
	char *const args[] = {"ls", NULL};
	char *const envp[] = {NULL};
	execve("/usr/bin/ls", args, envp);
	perror("execve");
	exit(EXIT_FAILURE); // Make sure to exit the child process if execve fails
}

int	main(void)
{
	pid_t pid;

	printf("Hi I am the main process. My PID is :%d\n", getpid());
	pid = fork();
	if (pid == -1)
		printf("Error while forking\n");
	else if (pid == 0)
	{
		printf("I am the child. But now a new parent. My PID is :%d --- My child's PID is%d\n", getpid(), pid);
		callexecve();
	}
	else if (pid > 1)
	{
		printf("I am the parent. My PID is :%d --- My child's PID is %d\n",
			getpid(), pid);
		waitpid(pid, NULL, 0);
		printf("Got back the control?\n");
	}
}