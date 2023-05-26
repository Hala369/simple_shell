#include "main.h"
/**
* _puts - writes a string
* @str: string to write
* Return: number of chars printed or -1 on failure
*/
ssize_t _puts(char *str)
{
	ssize_t n, l;

	n = _strlen(str);
	l = write(STDOUT_FILENO, str, n);
	if (l != n)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (l);
}
/**
* _strdup - returns pointer
* @strtodup: string to be duplicated
* Return: a pointer to the new duplicated string
*/
char *_strdup(char *strtodup)
{
	char *c;

	int l, i;

	if (strtodup == 0)
		return (NULL);

	for (l = 0; strtodup[l]; l++)
		;
	c = malloc((l + 1) * sizeof(char));

	for (i = 0; i <= l; i++)
		c[i] = strtodup[i];

	return (c);
}
/**
* _strcmpr - compares two strings
* @strcmp1: first string, of two, to be compared in length
* @strcmp2: second string, of two, to be compared
* Return: 0 on success, anything else is a failure
*/
int _strcmpr(char *strcmp1, char *strcmp2)
{
	int x;

	x = 0;
	while (strcmp1[x] == strcmp2[x])
	{
		if (strcmp1[x] == '\0')
			return (0);
		x++;
	}
	return (strcmp1[x] - strcmp2[x]);
}
/**
* _strcat - concatenates two strings
* @strc1: first string
* @strc2: second string
* Return: pointer
*/
char *_strcat(char *strc1, char *strc2)
{
	char *ns;
	unsigned int l1, l2, nl, i, j;

	l1 = 0;
	l2 = 0;
	if (strc1 == NULL)
		l1 = 0;
	else
	{
		for (l1 = 0; strc1[l1]; l1++)
			;
	}
	if (strc2 == NULL)
		l2 = 0;
	else
	{
		for (l2 = 0; strc2[l2]; l2++)
			;
	}
	nl = l1 + l2 + 2;
	ns = malloc(nl * sizeof(char));
	if (ns == NULL)
		return (NULL);
	for (i = 0; i < l1; i++)
		ns[i] = strc1[i];
	ns[i] = '/';
	for (j = 0; j < l2; j++)
		ns[i + 1 + j] = strc2[j];
	ns[l1 + l2 + 1] = '\0';
	return (ns);
}
/**
* _strlen - returns the length of a string
* @str: string to be measured
* Return: length of string
*/
unsigned int _strlen(char *str)
{
	unsigned int l;

	l = 0;

	for (l = 0; str[l]; l++)
		;
	return (l);
}
