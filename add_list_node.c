#include "main.h"

/**
 * add_list_node - adds a new node to end of linked list of PATH
 * @head: pointer to the first node in the list
 * @str: string to create new node with
 * @args: pointer to made arguments
 *
 * Return: pointer to the new node added
 */
list_t *add_list_node(list_t **head, char *str, arg_t *args)
{
	list_t *temp = *head, *temp1;
	char *new_string;

	new_string = strdup(str);
	temp1 = (list_t *)malloc(sizeof(list_t));
	if (temp1 == NULL)
	{
		perror(args->exe);
		exit(EXIT_FAILURE);
	}
	temp1->directory = new_string;
	temp1->next = NULL;
	if (*head == NULL)
	{
		*head = temp1;
		return (temp1);
	}
	while (temp->next)
		temp = temp->next;
	temp->next = temp1;
	return (temp1);
}

/**
 * add_env_node - adds a new node to end of linked list of environment variable
 * @head: pointer to the first node in the list
 * @var: pointer to variable name
 * @val: pointer to value of variable
 * @args: pointer to main arguments
 *
 * Return: pointer to new node added
 */
env_t *add_env_node(env_t **head, char *var, char *val, arg_t *args)
{
	env_t *temp = *head, *temp1;
	char *new_var, *new_val;

	new_var = strdup(var);
	new_val = _strdup(val);
	if (new_var == NULL || new_val == NULL)
	{
		perror(args->exe);
		exit(EXIT_FAILURE);
	}
	temp1 = (env_t *)malloc(sizeof(env_t));
	if (temp1 == NULL)
	{
		perror(args->exe);
		exit(EXIT_FAILURE);
	}
	temp1->var = new_var;
	temp1->val = new_val;
	temp1->next = NULL;
	if (*head == NULL)
	{
		*head = temp1;
		return (temp1);
	}
	while ((*head)->next)
		*head = (*head)->next;
	(*head)->next = temp1;
	*head = temp;
	return (temp1);
}

coms_t *add_coms_node(coms_t **head, char **commands, char *operator, arg_t *args)
{
	coms_t *temp = *head, *temp1;
	char **new_commands, *new_operator;

	new_commands = copy_string_array(commands);
	new_operator = _strdup(operator);
	if (new_commands == NULL)
	{
		perror(args->exe);
		exit(EXIT_FAILURE);
	}
	temp1 = (coms_t *)malloc(sizeof(coms_t));
	if (temp1 == NULL)
	{
		perror(args->exe);
		exit(EXIT_FAILURE);
	}
	temp1->commands = new_commands;
	temp1->operator = new_operator;
	temp1->next = NULL;
	if (*head == NULL)
	{
		*head = temp1;
		return (temp1);
	}
	while ((*head)->next)
		*head = (*head)->next;
	(*head)->next = temp1;
	*head = temp;
	return (temp1);
}