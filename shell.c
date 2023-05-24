#include "main.h"
/**
 *
 * UNIX command line interpreter.
 *
 *
 **/
int main(void)
{
	char input[BUFFER_SIZE];
	char prompt[] = "ALX: ";

	while (1)
	{
	printf("%s", prompt);

	if (fgets(input, BUFFER_SIZE, stdin) == NULL)
	{
		printf("\n");
		break;
	}
	input[strcspn(input, "\n")] = '\0';
	if (strlen(input) == 0)
	{
		continue;
	}
	if (strcmp(input, "exit") == 0)
	{
		break;
	}
	char *token = strtok(input, TOKEN_DELIMITERS), *command = token, *arguments[BUFFER_SIZE];
	int arg_index = 0;

	while (token != NULL)
	{
		arguments[arg_index] = token;
		arg_index++;
		token = strtok(NULL, TOKEN_DELIMITERS);
	}
	arguments[arg_index] = NULL; // Set the last element to NULL
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
		}
	if (pid == 0)
	{
	if (execvp(command, arguments) == -1)
	{
	perror("exec");
	exit(EXIT_FAILURE);
		}
	} else
	{
	wait(NULL); // Wait for the child process to complete
	}
	}
	printf("thallaw...\n");

	return 0;
}
