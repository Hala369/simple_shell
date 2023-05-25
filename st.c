#include "main.h"
/**
* _puts - writes a string
* @str: string to write
* Return: number of chars printed or -1 on failure
*/
ssize_t _puts(char *str)
{
	ssize_t n;
	ssize_t l;

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

	int l;
	int b;

	if (strtodup == 0)
		return (NULL);

	for (l = 0; strtodup[l]; l++)
		;
	c = malloc((l + 1) * sizeof(char));

	for (b = 0; b <= l; b++)
		c[b] = strtodup[b];

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
	int b;

	b = 0;
	while (strcmp1[b] == strcmp2[b])
	{
		if (strcmp1[b] == '\0')
			return (0);
		b++;
	}
	return (strcmp1[b] - strcmp2[b]);
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
	unsigned int l1, l2, nl, b, c;

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
	for (b = 0; b < l1; b++)
		ns[b] = strc1[b];
	ns[b] = '/';
	for (c = 0; c < l2; c++)
		ns[b + 1 + c] = strc2[c];
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
		return (l);
}
