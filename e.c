#include "main.h"
/**
* print_error - prints error messages
* @vars: pointer
* @msg: message to print
* Return: void
*/
void print_error(vars_t *vars, char *msg)
{
	char *count;

	_puts2(vars->argv[0]);
	_puts2(": ");
	count = _uitoa(vars->count);
	_puts2(count);
	free(count);
	_puts2(": ");
	_puts2(vars->av[0]);
	if (msg)
	{
		_puts2(msg);
	}
	else
		perror("");
}
/**
* _puts2 - prints a string
* @str: string to print
* Return: void
*/
void _puts2(char *str)
{
	ssize_t n;
	ssize_t l;

	n = _strlen(str);
	l = write(STDERR_FILENO, str, n);
	if (l != n)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
* _uitoa - converts an unsigned int to a string
* @count: unsigned int to convert
* Return: pointer to the converted string
*/
char *_uitoa(unsigned int count)
{
	char *k;
	unsigned int t;
	unsigned int d;

	t = count;
	for (d = 0; t != 0; d++)
		t /= 10;
	k = malloc(sizeof(char) * (d + 1));
	if (k == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	k[d] = '\0';
	for (--d; count; --d)
	{
		k[d] = (count % 10) + '0';
		count /= 10;
	}
	return (k);
}
