#include "main.h"
/**
* make_env - make the shell environment from the environment passed to main
* @env: environment passed to main
* Return: pointer to the new environment
*/
char **make_env(char **env)
{
	char **n = NULL;
	size_t x;

	for (x = 0; env[x] != NULL; x++)
		;
	n = malloc(sizeof(char *) * (x + 1));
	if (n == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (x = 0; env[x] != NULL; x++)
		n[x] = _strdup(env[x]);
	n[x] = NULL;
	return (n);
}
/**
* free_env - free the shell's environment
* @env: shell's environment
* Return: void
*/
void free_env(char **env)
{
	unsigned int x;

	for (x = 0; env[x] != NULL; x++)
		free(env[x]);
	free(env);
}
