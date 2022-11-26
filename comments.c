#include "main.h"

/**
 * check_comments - makes sure commented commands are ignored
 * @args: arguments structure
 */
void check_comments(arg_t *args)
{
	int i;
	char **new_commands = NULL;

	for (i = 1; args->commands[i - 1] != NULL; i++)
	{
		if (args->commands[i - 1][0] == '#' || strcmp(args->commands[i - 1], "#") == 0)
			break;
		new_commands = _realloc(new_commands, i, args->commands[i - 1]);
	}
	new_commands = _realloc(new_commands, i, NULL);
	free_strings_array(args->commands);
	args->commands = new_commands;
	args->command = new_commands[0];
}
