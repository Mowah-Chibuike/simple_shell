#include "main.h"

/**
 * read_line - executes commands passed into it
 * @args: argument structure
 *
 * Return: line read
 */
char *read_line(arg_t *args)
{
	char *command_line = NULL;
	size_t n = 0;

	if (getline(&command_line, &n, stdin) == -1)
	{
		write(1, "\n", 1);
		if (errno == 0)
			exit(EXIT_SUCCESS);
		else
		{
			perror(args->exe);
			exit(EXIT_FAILURE);
		}
	}
	return (command_line);
}

/**
 * launch_prompt - starts reading from the standard input
 * @args: arguments structure
 *
 * Return: void
 */
int launch_prompt(arg_t *args)
{
	int i;
	char *line, **commands;
	int exit_status;

	while (1)
	{
		write(1, "$ ", 2);
		line = read_line(args);
		commands = get_args(line);
		if (commands != NULL)
		{
			args->commands = commands;
			args->command = commands[0];
			if (execute(args) == -1)
				break;
		}
		free(line);
		if (args->commands != NULL)
		{
			for (i = 0; commands[i] != NULL; i++)
				free(commands[i]);
			free(args->commands);
		}
	}
	free(line);
	exit_status = args->exit_status;
	free_all(args);
	return (exit_status);
}

/**
 * main - launches a new shell environment
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: always 0
 */
int main(int argc, char *argv[])
{
	int exit_status;
	arg_t *args = NULL;

	if (argc != 1)
	{
		write(2, "Usage: simple_shell", 19);
		return (1);
	}
	args = shell_init();
	args->exe = argv[0];
	/* launch the prompt and start reading commands */
	exit_status = launch_prompt(args);
	return (exit_status);
}
