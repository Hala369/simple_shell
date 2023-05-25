#include "main.h"
/**
* tokenize - tokenizes a buffer
* @buffer: buffer to tokenize
* @delimiter: delimiter to tokenize along
* Return: pointer to an array
*/
char **tokenize(char *buffer, char *delimiter)
{
	char **t = NULL;
	size_t y = 0, mcount = 10;

	if (buffer == NULL)
		return (NULL);
	t = malloc(sizeof(char *) * mcount);
	if (t == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	while ((t[y] = new_strtok(buffer, delimiter)) != NULL)
	{
		y++;
		if (y == mcount)
		{
			t = _realloc(t, &mcount);
			if (t == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		buffer = NULL;
	}
	return (t);
}
