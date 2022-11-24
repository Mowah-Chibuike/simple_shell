#include "main.h"

/**
 * check_for_alias - checks for an alias
 * @args: arguments structure
 */
void check_for_alias(arg_t *args)
{
	alias_t *temp = args->alias_link, *temp1 = args->alias_link;
	char *command = args->command, *alias, **val;

	while (temp != NULL)
	{
		alias = temp->alias;
		if (strcmp(alias, command) == 0)
		{
			val = copy_string_array(temp->val);
			while (temp1 != NULL)
			{
				alias = temp1->alias;
				if (strcmp(alias, val[0]) == 0)
				{
					free_strings_array(val);
					val = copy_string_array(temp1->val);
					free_strings_array(args->commands);
					args->commands = val;
					args->command = val[0];
					return;
				}
				temp1 = temp->next;
			}
			free_strings_array(args->commands);
			args->commands = val;
			args->command = val[0];
		}
		temp = temp->next;
	}
}

/**
 * check_for_equality - checks argument for equality character
 * @str: string to be checked
 *
 * Return: 1 if equality symbol is found, otherwise 0
 */
int check_for_equality(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		if (str[i] == '=')
			return (1);
	return (0);
}

/**
 * locate_alias - locate an alias in the linked list
 * @args: arguments structure
 * @alias: alias to be located
 *
 * Return: node containing the particular alias
 */
alias_t *locate_alias(arg_t *args, char *alias)
{
	alias_t *temp = args->alias_link;

	while (temp != NULL)
	{
		if (strcmp(alias, temp->alias) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/**
 * mutate_alias - updates the alias linked list
 * @args: arguments structure
 * @str: alias command
 */
void mutate_alias(arg_t *args, char *str)
{
	alias_t *node, **temp = &args->alias_link;
	char *alias, *val_string, **val, *temp1, *temp2, *temp3, *alias_string;
	char *cp1 = _strdup(str);

	alias = strtok(cp1, "=");
	val_string = strtok(NULL, "");
	temp1 = _strdup(val_string);
	val = get_alias_val(temp1);
	free(temp1);
	temp1 = _strcat(alias, "=");
	temp2 = _strcat(temp1, "\'");
	temp3 = _strcat(temp2, val_string);
	alias_string = _strcat(temp3, "\'");
	node = locate_alias(args, alias);
	if (node == NULL)
	{
		if (add_alias_node(temp, alias, val, alias_string) == NULL)
			perror(args->exe);
	}
	else
	{
		free_strings_array(node->val);
		free(node->alias_string);
		node->val = copy_string_array(val);
		node->alias_string = alias_string;
	}
	free(cp1);
	free(temp1);
	free(temp2);
	free(temp3);
	free(alias_string);
	free_strings_array(val);
}

/**
 * handle_alias - handles the alias command
 * @args: arguments structure
 *
 * Return: always 0
 */
int handle_alias(arg_t *args)
{
	int i, err;
	char *exe = args->exe, *temp1, *temp2;
	alias_t *node;

	if (args->commands[1] == NULL)
	{
		print_list(args->alias_link);
		return (0);
	}
	for (i = 1; args->commands[i] != NULL; i++)
	{
		if (check_for_equality(args->commands[i]))
		{
			if (args->commands[i + 1] != NULL && args->commands[i + 1][0] == '-')
			{
				temp1 = _strcat(args->commands[i], " ");
				temp2 = _strcat(temp1, args->commands[i + 1]);
				mutate_alias(args, temp2);
				free(temp1);
				free(temp2);
				i += 1;
			}
			else
				mutate_alias(args, args->commands[i]);
		}
		else
		{
			node = locate_alias(args, args->commands[i]);
			if (node == NULL)
			{
				args->exit_status = args->exit = 127;
				args->errors += 1;
				err = args->errors;
				_dprintf(2, "%s: %d: alias: %s: not found\n", exe, err, args->commands[i]);
			}
			else
				_dprintf(1, "%s\n", node->alias_string);
		}
	}
	return (0);
}
