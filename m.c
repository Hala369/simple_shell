#include "main.h"
/**
* _realloc - reallocates a pointer
* @ptr: pointer to the old array
* @size: pointer to number in the old array
* Return: pointer to the new array
*/
char **_realloc(char **ptr, size_t *size)
{
	char **n;
	size_t f;

	n = malloc(sizeof(char *) * ((*size) + 10));
	if (n == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (f = 0; f < (*size); f++)
	{
		n[f] = ptr[f];
	}
	*size += 10;
	free(ptr);
	return (n);
}
