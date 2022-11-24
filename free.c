#include "main.h"

/**
 * free_path - frees the path linked list
 * @head: pointer to the head node of the linked list
 *
 * Return: void
 */
void free_path(list_t **head)
{
	list_t *temp;

	while (*head != NULL)
	{
		temp = (*head)->next;
		free((*head)->directory);
		free(*head);
		*head = temp;
	}
}

/**
 * free_env_node - frees a node of an env linked list
 * @node: node to be deleted
 *
 * Return: void
 */
void free_env_node(env_t **node)
{
	free((*node)->var);
	free((*node)->val);
	free(*node);
}

/**
 * free_env - frees the environment linked list
 * @head: env_t linked list
 *
 * Return: void
 */
void free_env(env_t **head)
{
	env_t *temp;

	while (*head != NULL)
	{
		temp = (*head)->next;
		free((*head)->var);
		free((*head)->val);
		free(*head);
		*head = temp;
	}
}

/**
 * free_coms - frees a command linked list
 * @head: pointer to the first node of the linked list
 *
 * Return: void
 */
void free_coms(coms_t *head)
{
	coms_t *temp;
	char **commands;

	(void)commands;
	while (head != NULL)
	{
		temp = head->next;
		free_strings_array(head->commands);
		free(head->operator);
		free(head);
		head = temp;
	}
}

/**
 * free_all - frees all arguments
 * @args: arguments structure
 *
 * Return: void
 */
void free_all(arg_t *args)
{
	free_strings_array(args->_environ);
	free_env(&args->environment);
	free_path(&args->path);
	free_alias(args->alias_link);
	free(args);
}
