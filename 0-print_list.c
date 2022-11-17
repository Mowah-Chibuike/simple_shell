#include "main.h"
#include <stdio.h>

/**
 * print_list - prints all the elements of a list_t list
 * @h: pointer to the linked list to be printed
 *
 * Return: number of nodes
 *//*
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
}*/

void print_list(coms_t *h)
{
	char **commands;
	coms_t *temp = h;
	int i, n;

	n = 0;
	while (temp != NULL)
	{
		printf("print_list: %d\n", n);
		n++;
		commands = temp->commands;
		for (i = 0; commands[i] != NULL; i++)
			printf("print_list: %s ", commands[i]);
		printf("\n");
		temp = temp->next;
	}
}
