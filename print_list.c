#include "main.h"
#include <stdio.h>

/**
 * print_list - prints all the elements of a list_t list
 * @h: pointer to the linked list to be printed
 *
 * Return: number of nodes
 */
/*
size_t print_list(env_t *h)
{
	env_t *temp = h;
	size_t n = 0;

	while (temp != NULL)
	{
		if (temp->var == NULL)
			printf("[0] (nil)\n");
		else
			printf("%s=%s\n", temp->var, temp->val);
		n++;
		temp = temp->next;
	}
	return (n);
}
*/

void print_list(alias_t *h)
{
	alias_t *temp = h;

	while (temp != NULL)
	{
		_dprintf(1, "%s\n", temp->alias_string);
		temp = temp->next;
	}
}
