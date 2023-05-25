#include "main.h"
/**
* path_execute - executes a command
* @command: full path to the command
* @vars: pointer
* Return: 0 on succcess, 1 on failure
*/
int path_execute(char *command, vars_t *vars)
{
	pid_t child_pid;

	if (access(command, X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
			print_error(vars, NULL);
		if (child_pid == 0)
		{
			if (execve(command, vars->av, vars->env) == -1)
				print_error(vars, NULL);
		}
		else
		{
			wait(&vars->status);
			if (WIFEXITED(vars->status))
				vars->status = WEXITSTATUS(vars->status);
			else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
				vars->status = 130;
			return (0);
		}
		vars->status = 127;
		return (1);
	}
	else
	{
		print_error(vars, ": Permission denied\n");
		vars->status = 126;
	}
	return (0);
}
/**
* find_path - finds the PATH variable
* @env: array of environment variables
* Return: pointer to the node that contains the PATH, or NULL on failure
*/
char *find_path(char **env)
{
	char *p = "PATH=";
	unsigned int q;
	unsigned int s;

	for (q = 0; env[q] != NULL; q++)
	{
		for (s = 0; s < 5; s++)
			if (p[s] != env[q][s])
				break;
		if (s == 5)
			break;
	}
	return (env[q]);
}
/**
* check_for_path - checks if the command is in the PATH
* @vars: variables
* Return: void
*/
void check_for_path(vars_t *vars)
{
	char *p, *pd = NULL, *check = NULL;
	unsigned int q = 0, u = 0;
	char **pt;
	struct stat buf;

	if (check_for_dir(vars->av[0]))
		u = execute_cwd(vars);
	else
	{
		p = find_path(vars->env);
		if (p != NULL)
		{
			pd = _strdup(p + 5);
			pt = tokenize(pd, ":");
			for (q = 0; pt && pt[q]; q++, free(check))
			{
				check = _strcat(pt[q], vars->av[0]);
				if (stat(check, &buf) == 0)
				{
					u = path_execute(check, vars);
					free(check);
					break;
				}
			}
			free(pd);
			if (pt == NULL)
			{
				vars->status = 127;
				new_exit(vars);
			}
		}
		if (p == NULL || pt[q] == NULL)
		{
			print_error(vars, ": not found\n");
			vars->status = 127;
		}
		free(pt);
	}
	if (u == 1)
		new_exit(vars);
}
/**
* execute_cwd - executes the command
* @vars: pointer to struct of variables
* Return: 0 on success, 1 on failure
*/
int execute_cwd(vars_t *vars)
{
	pid_t child_pid;
	struct stat buf;

	if (stat(vars->av[0], &buf) == 0)
	{
		if (access(vars->av[0], X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
				print_error(vars, NULL);
			if (child_pid == 0)
			{
				if (execve(vars->av[0], vars->av, vars->env) == -1)
					print_error(vars, NULL);
			}
			else
			{
				wait(&vars->status);
				if (WIFEXITED(vars->status))
					vars->status = WEXITSTATUS(vars->status);
				else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
					vars->status = 130;
				return (0);
			}
			vars->status = 127;
			return (1);
		}
		else
		{
			print_error(vars, ": Permission denied\n");
			vars->status = 126;
		}
		return (0);
	}
	print_error(vars, ": not found\n");
	vars->status = 127;
	return (0);
}
/**
* check_for_dir - checks if the command is a part of a path
* @str: command
* Return: 1 on success, 0 on failure
*/
int check_for_dir(char *str)
{
	unsigned int q;

	for (q = 0; str[q]; q++)
	{
		if (str[q] == '/')
			return (1);
	}
	return (0);
}
