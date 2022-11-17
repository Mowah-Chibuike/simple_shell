#include "main.h"

/**
 * execute_command - executes command
 * @args: arguments structure
 *
 * Return: void
 */
pid_t execute_path(arg_t *args)
{
	int status;
	pid_t pid, wpid;
	char **commands, *command;

	if (args->commands == NULL)
		return (1);
	search_path(args);
	commands = args->commands;
	command = args->command;
	pid = fork();
	if (pid == -1)
	{
		perror(args->exe);
		return (1);
	}
	else if (pid == 0)
	{
		if (execve(command, commands, args->_environ) == -1)
		{
			perror(args->exe);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* parent process */
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
			if (wpid == -1)
			{
				perror(args->exe);
				return (1);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free(args->command);
	args->command = NULL;
	free(args->commands);
	args->commands = NULL;
	return (0);
}

/**
 * exec_builtins - execute shell builtin functions
 * @args: arguments structure
 *
 * Return: 0 if successful and 1 otherwise
 */
int exec_builtins(arg_t *args)
{
	int i;
	char **commands;
	builtins_t builtin_commands[] = {
		{"exit", shell_exit},
		{"env", print_env},
		{"setenv", set_env},
		{"unsetenv", un_set_env},
		{"cd", change_dir},
		{NULL, NULL}
	};

	commands = args->commands;
	for (i = 0; builtin_commands[i].command; i++)
	{
		if (_strcmp(commands[0], builtin_commands[i].command) == 0)
			return (builtin_commands[i].builtin(args));
	}

	return (1);
}

/**
 * execute_commands - runs any shell command
 * @args: arguments structure
 *
 * Return: the exit status
 */
int execute_commands(arg_t *args)
{
	if (args->commands == NULL)
		return (1);
	if (exec_builtins(args) == 1)
		return (execute_path(args));
	return (args->exit);
}

/**
 * execute - handles every execution in the shell
 * @args: argument structure
 *
 * Return: the exit status
 */
int execute(arg_t *args)
{
	int i, exit_status;
	char *op = NULL, **commands, **dup;
	coms_t *head;

	if (args->commands == NULL)
		return (1);
	dup = copy_string_array(args->commands);
	head = get_commands(args, dup);
	commands = args->commands;
	for (i = 0; commands[i] != NULL; i++)
		free(commands[i]);
	free(args->commands);
	while (head != NULL)
	{
		commands = head->commands;
		args->commands = commands;
		args->command = commands[0];
		if (op != NULL && (strcmp(op, ";") == 0 || strcmp(op, "||") == 0))
			exit_status = execute_commands(args);
		else if (op != NULL && strcmp(op, "&&") == 0)
		{
			if (exit_status == 0)
				exit_status = execute_commands(args);
		}
		else
			exit_status = execute_commands(args);
		if (exit_status == -1)
		{
			for (i = 0; dup[i] != NULL; i++)
				free(dup[i]);
			free(dup);
			free_coms(&head);
			return (-1);
		}
		op = head->operator;
		head = head->next;
	}
	for (i = 0; dup[i] != NULL; i++)
		free(dup[i]);
	free(dup);
	free_coms(&head);
	return (exit_status);
}
