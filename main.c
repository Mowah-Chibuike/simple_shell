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

	(void)args;
	if (getline(&command_line, &n, stdin) == -1)
	{
		write(1, "\n", 1);
		if (errno == 0)
			exit(EXIT_SUCCESS);
		else
			exit(EXIT_FAILURE);
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
	}
	free(line);
	exit_status = args->exit_status;
	return (exit_status);
}

/**
 * non_interactive - runs commands in non interactive mode
 * @args: arguments structure
 *
 * Return: exit status after executing
 */
int non_interactive(arg_t *args)
{
	char *line, **commands;
	int exit_status;

	line = read_line(args);
	while (line != NULL)
	{
		commands = get_args(line);
		if (commands != NULL)
		{
			args->commands = commands;
			args->command = commands[0];
			execute(args);
		}
		free(line);
		line = read_line(args);
	}
	free(line);
	exit_status = args->exit;
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
	int exit_status, fd;
	arg_t *args = NULL;

	(void)argc;
	fd = STDIN_FILENO;
	args = shell_init();
	args->exe = argv[0];
	/* launch the prompt and start reading commands */
	if (isatty(fd))
		exit_status = launch_prompt(args);
	else
		exit_status = non_interactive(args);
	free_all(args);
	return (exit_status);
}
