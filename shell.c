#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	else if (child_pid == 0)
	{
		char *args[] = {"/bin/ls", "-l", NULL};
		if (execve(args[0], args, NULL) == -1)
		{
			perror("execve error");
			_exit(1);
	}
}
else
	{
		wait(NULL);
		write(STDOUT_FILENO, "Child process executed.\n", 24);
	}

	return (0);
}
