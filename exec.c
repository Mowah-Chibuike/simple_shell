#include "main.h"
#include <signal.h>

/**
 * execute_path- executes command
 * @args: arguments structure
 *
 * Return: void
 */
pid_t execute_path(arg_t *args)
{
	int status;
	pid_t pid, wpid;
	char **commands, *command;

	search_path(args);
	commands = args->commands;
	command = args->command;
	pid = fork();
	if (pid == -1)
	{
		perror(args->exe);
		args->exit = errno;
		return (1);
	}
	else if (pid == 0)
	{
		if (execve(command, commands, args->_environ) == -1)
		{
			perror(args->exe);
			_exit(1);
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
				args->exit = errno;
				return (1);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		args->exit = WEXITSTATUS(status);
	}
	if (args->exit == 0)
		free_strings_array(commands);
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
		return (0);
	if (exec_builtins(args) == 1)
		execute_path(args);
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
	int exit_status;
	char *op = NULL, **commands, **dup;
	coms_t *head, *temp;

	args->exit = 0;
	if (args->commands == NULL)
		return (1);
	dup = copy_string_array(args->commands);
	head = get_commands(args, dup);
	temp = head;
	commands = args->commands;
	free_strings_array(commands);
	while (temp != NULL)
	{
		commands = temp->commands;
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
			free_strings_array(dup);
			free_coms(head);
			return (-1);
		}
		op = head->operator;
		temp = temp->next;
	}
	free_strings_array(dup);
	free_coms(head);
	return (exit_status);
}
