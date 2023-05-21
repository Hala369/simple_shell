#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define TOKEN_DELIMITERS " \t\n\r\a"

int main() {
	char input[BUFFER_SIZE];
	char prompt[] = "ALX: ";

	while (1) {
	printf("%s", prompt); // Display the prompt

	if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
		printf("\n"); // Print a newline if Ctrl+D is pressed
		break; // Exit the shell on end of file
	}
	input[strcspn(input, "\n")] = '\0'; // Remove trailing newline
	if (strlen(input) == 0) {
		continue; // Ignore empty commands and display the prompt again
	}
	if (strcmp(input, "exit") == 0) {
		break; // Exit the shell
	}
	char *token = strtok(input, TOKEN_DELIMITERS);
	char *command = token;
	char *arguments[BUFFER_SIZE];
	int arg_index = 0;

	while (token != NULL) {
		arguments[arg_index] = token;
		arg_index++;
		token = strtok(NULL, TOKEN_DELIMITERS);
	}
	arguments[arg_index] = NULL; // Set the last element to NULL
	pid_t pid = fork();

	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
		}
	if (pid == 0) {
	if (execvp(command, arguments) == -1) {
	perror("exec");
	exit(EXIT_FAILURE);
		}
	} else {
	wait(NULL); // Wait for the child process to complete
	}
	}
	printf("thallaw...\n");

	return 0;
}
