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
void free_coms(coms_t **head)
{
	int i;
	coms_t *temp;
	char **commands;

	while (*head != NULL)
	{
		temp = (*head)->next;
		commands = (*head)->commands;
		for (i = 0; commands[i] != NULL; i++)
			free(commands[i]);
		free(commands[i]);
		free((*head)->commands);
		free((*head)->operator);
		free(*head);
		*head = temp;
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
	int i;
	char **commands = args->commands;
	char **_environ = args->_environ;
	env_t *environment = args->environment;
	list_t *path = args->path;

	/**
	 * for (i = 0; commands[i] != NULL; i++)
	 * free(commands[i]);
	 * free(commands);
	*/
	(void)commands;
	for (i = 0; _environ[i] != NULL; i++)
		free(_environ[i]);
	free(_environ);
	free_env(&environment);
	free_path(&path);
	free(args);
}
