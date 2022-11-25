#include "main.h"
#include <stdio.h>

/**
 * print_list - prints all the elements of a list_t list
 * @h: pointer to the linked list to be printed
 *
 * Return: number of nodes
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
