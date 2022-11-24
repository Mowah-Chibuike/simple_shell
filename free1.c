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

/**
 * free_double - frees coms linked list and arrays of strings
 * @list: coms linked list
 * @array: array of strings to be freed
 *
 * Return: void
 */
void free_double(coms_t *list, char **array)
{
	free_coms(list);
	free_strings_array(array);
}

/**
 * free_alias - frees an alias linked list
 * @head: pointer to head node of the linked list
 */
void free_alias(alias_t *head)
{
	alias_t *temp;

	while (head != NULL)
	{
		temp = head->next;
		free(head->alias);
		free_strings_array(head->val);
		free(head->alias_string);
		free(head);
		head = temp;
	}
}
