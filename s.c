#include "main.h"
/**
* check_match - checks
* @c: character to check
* @str: string to check
* Return: 1 if match, 0 if not
*/
unsigned int check_match(char c, const char *str)
{
	unsigned int h;

	for (h = 0; str[h] != '\0'; h++)
	{
		if (c == str[h])
			return (1);
	}
	return (0);
}

/**
* new_strtok - custom strtok
* @str: string to tokenize
* @delim: delimiter to tokenize against
* Return: pointer to the next token or NULL
*/
char *new_strtok(char *str, const char *delim)
{
	static char *t;
	static char *n;
	unsigned int h;

	if (str != NULL)
		n = str;
	t = n;
	if (t == NULL)
		return (NULL);
	for (h = 0; n[h] != '\0'; h++)
	{
		if (check_match(n[h], delim) == 0)
			break;
	}
	if (n[h] == '\0' || n[h] == '#')
	{
		n = NULL;
		return (NULL);
	}
	t = n + h;
	n = t;
	for (h = 0; n[h] != '\0'; h++)
	{
		if (check_match(n[h], delim) == 1)
			break;
	}
	if (n[h] == '\0')
		n = NULL;
	else
	{
		n[h] = '\0';
		n = n + h + 1;
		if (*n == '\0')
			n = NULL;
	}
	return (t);
}
