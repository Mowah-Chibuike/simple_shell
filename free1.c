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

	if (array != NULL)
	{
		for (i = 0; array[i] != NULL; i++)
		{
			if (array[i] != NULL)
			{
				free(array[i]);
				array[i] = NULL;
			}
		}
		free(array[i]);
		free(array);
		array = NULL;
	}
}
