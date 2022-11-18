#include "main.h"

/**
 * free_strings_array - frees an array of strings
 * @array: array to be freed
 *
 * Return: void
 */
void free_strings_array(char **array)
{
	int i;
	char ***mem = &array;

	if (array != NULL)
	{
		for (i = 0; array[i] != NULL; i++)
		{
			free(array[i]);
			array[i] = NULL;
		}
		free(array[i]);
		free(array);
		*mem = NULL;
	}
}
