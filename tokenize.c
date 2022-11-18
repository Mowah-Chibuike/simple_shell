#include "main.h"

/**
 * get_args  - get information from the input to stdin
 * @command_line: string from the stdin
 *
 * Return: tokens from the stdin
 */
char **get_args(char *command_line)
{
	int size = 1;
	char **tokens = NULL;
	char *token, *delim = " \n\t\r\a";

	token = strtok(command_line, delim);
	if (token == NULL)
		return (NULL);
	while (token != NULL)
	{
		tokens = _realloc(tokens, size, token);
		size++;
		token = strtok(NULL, delim);
	}
	tokens = _realloc(tokens, size, NULL);
	return (tokens);
}

/**
 * extract_commands - extracts commands from an array of strings
 * @commands: list of strings to extract commands from
 * @index: position in the array of strings
 *
 * Return: commands extracted
 */

char **extract_commands(char **commands, int *index)
{
	int i, j, k, flag = 0;
	char **token = NULL, *operators[4] = {";",  "||", "&&", NULL};

	for (i = *index, k = 1; commands[i] != NULL; i++, *index += 1, k++)
	{
		for (j = 0; operators[j] != NULL; j++)
			if (strcmp(commands[i], operators[j]) == 0)
			{
				flag = 1;
				break;
			}
		if (flag == 1)
			break;
		token = _realloc(token, k, commands[i]);
	}
	token = _realloc(token, k, NULL);
	return (token);
}

/**
 * get_commands - gets commands from and array of commands
 * @args: argument structure
 * @commands: array to get commands from
 *
 * Return: linked list of commands
 */
coms_t *get_commands(arg_t *args, char **commands)
{
	int i;
	coms_t *head = NULL;
	char **tokens, *operator;

	i = 0;
	while (commands[i] != NULL)
	{
		tokens = extract_commands(commands, &i);
		operator = commands[i];
		add_coms_node(&head, tokens, operator, args);
		if (commands[i] != NULL)
			i++;
		free_strings_array(tokens);
	}
	return (head);
}

