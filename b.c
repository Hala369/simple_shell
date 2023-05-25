#include "main.h"
/**
* check_for_builtins - checks if the command is a builtin
* @vars: variables
* Return: pointer to the function or NULL
*/
void (*check_for_builtins(vars_t *vars))(vars_t *vars)
{
	unsigned int h;
	builtins_t check[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};

	for (h = 0; check[h].f != NULL; h++)
	{
		if (_strcmpr(vars->av[0], check[h].name) == 0)
			break;
	}
	if (check[h].f != NULL)
		check[h].f(vars);
	return (check[h].f);
}

/**
* new_exit - exit program
* @vars: variables
* Return: void
*/
void new_exit(vars_t *vars)
{
	int status;

	if (_strcmpr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		status = _atoi(vars->av[1]);
		if (status == -1)
		{
			vars->status = 2;
			print_error(vars, ": Illegal number: ");
			_puts2(vars->av[1]);
			_puts2("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->status = status;
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	free_env(vars->env);
	exit(vars->status);
}

/**
* _env - prints the current environment
* @vars: struct of variables
* Return: void.
*/
void _env(vars_t *vars)
{
	unsigned int h;

	for (h = 0; vars->env[h]; h++)
	{
		_puts(vars->env[h]);
		_puts("\n");
	}
	vars->status = 0;
}

/**
* new_setenv - create a new environment variable, or edit an existing variable
* @vars: pointer to struct of variables
* Return: void
*/
void new_setenv(vars_t *vars)
{
	char **k, *v;

	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	k = find_key(vars->env, vars->av[1]);
	if (k == NULL)
		add_key(vars);
	else
	{
		v = add_value(vars->av[1], vars->av[2]);
		if (v == NULL)
		{
			print_error(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			free_env(vars->env);
			exit(127);
		}
		free(*k);
		*k = v;
	}
	vars->status = 0;
}

/**
* new_unsetenv - remove an environment variable
* @vars: pointer
* Return: void
*/
void new_unsetenv(vars_t *vars)
{
	char **k;
	char **n;

	unsigned int a;
	unsigned int b;

	if (vars->av[1] == NULL)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	k = find_key(vars->env, vars->av[1]);
	if (k == NULL)
	{
		print_error(vars, ": No variable to unset");
		return;
	}
	for (a = 0; vars->env[a] != NULL; a++)
		;
	n = malloc(sizeof(char *) * a);
	if (n == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (a = 0; vars->env[a] != *k; a++)
		n[a] = vars->env[a];
	for (b = a + 1; vars->env[b] != NULL; b++, a++)
		n[a] = vars->env[b];
	n[a] = NULL;
	free(*k);
	free(vars->env);
	vars->env = n;
	vars->status = 0;
}
