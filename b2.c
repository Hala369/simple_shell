#include "main.h"
/**
* add_key - create a new environment
* @vars: pointer
* Return: void
*/
void add_key(vars_t *vars)
{
	unsigned int w;
	char **n;

	for (w = 0; vars->env[w] != NULL; w++)
		;
	n = malloc(sizeof(char *) * (w + 2));
	if (n == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (w = 0; vars->env[w] != NULL; w++)
		n[w] = vars->env[w];
	n[w] = add_value(vars->av[1], vars->av[2]);
	if (n[w] == NULL)
	{
		print_error(vars, NULL);
		free(vars->buffer);
		free(vars->commands);
		free(vars->av);
		free_env(vars->env);
		free(n);
		exit(127);
	}
	n[w + 1] = NULL;
	free(vars->env);
	vars->env = n;
}

/**
* find_key - finds an environment variable
* @env: array of environment variables
* @key: environment variable to find
* Return: pointer to address of the environment variable
*/
char **find_key(char **env, char *key)
{
	unsigned int w;
	unsigned int x;
	unsigned int l;

	l = _strlen(key);
	for (w = 0; env[w] != NULL; w++)
	{
		for (x = 0; x < l; x++)
			if (key[x] != env[w][x])
				break;
		if (x == l && env[w][x] == '=')
			return (&env[w]);
	}
	return (NULL);
}

/**
* add_value - create a new environment variable
* @key: variable name
* @value: variable value
* Return: pointer to the new string;
*/
char *add_value(char *key, char *value)
{
	unsigned int l1;
	unsigned int l2;
	unsigned int w;
	unsigned int x;
	char *n;

	l1 = _strlen(key);
	l2 = _strlen(value);
	n = malloc(sizeof(char) * (l1 + l2 + 2));
	if (n == NULL)
		return (NULL);
	for (w = 0; key[w] != '\0'; w++)
		n[w] = key[w];
	n[w] = '=';
	for (x = 0; value[x] != '\0'; x++)
		n[w + 1 + x] = value[x];
	n[w + 1 + x] = '\0';
	return (n);
}

/**
* _atoi - converts a string into an integer
* @str: string to convert
* Return: the integer value, or -1 if an error occurs
*/
int _atoi(char *str)
{
	unsigned int w;
	unsigned int d;
	int n = 0, num_test;

	num_test = INT_MAX;
	for (d = 0; num_test != 0; d++)
		num_test /= 10;
	for (w = 0; str[w] != '\0' && w < d; w++)
	{
		n *= 10;
		if (str[w] < '0' || str[w] > '9')
			return (-1);
		if ((w == d - 1) && (str[w] - '0' > INT_MAX % 10))
			return (-1);
		n += str[w] - '0';
		if ((w == d - 2) && (str[w + 1] != '\0') && (n > INT_MAX / 10))
			return (-1);
	}
	if (w > d)
		return (-1);
	return (n);
}
