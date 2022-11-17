#include "main.h"

/**
 * shell_exit - exits the shell
 * @args: argument structure
 *
 * Return: always 0
 */
int shell_exit(arg_t *args)
{
	char **commands = args->commands;

	if (commands[1] == NULL)
	{
		args->exit = -1;
		args->exit_status = 0;
	}
	else if (check_string(commands[1]))
	{
		if (commands[2] != NULL)
		{
			args->exit = 1;
			_dprintf(2, "%s: Excess arguments passed\n", args->exe);
			return (0);
		}
		args->exit = -1;
		args->exit_status = _atoi(commands[1]);
	}
	else
	{
		_dprintf(2, "%s: Invalid argument passed\n", args->exe);
		args->exit = 1;
	}

	return (0);
}

/**
 * print_env - prints environment variables
 * @args: arguments structure
 *
 * Return: always 0
 */
int print_env(arg_t *args)
{
	int i;
	char **_environ = args->_environ;

	for (i = 0; _environ[i] != NULL; i++)
		_dprintf(1, "%s\n", _environ[i]);
	args->exit = 0;
	return (0);
}

/**
 * set_env - adds a new environment variable or modifies an existing one
 * @args: arguments structure
 *
 * Return: always 0
 */
int set_env(arg_t *args)
{
	char **commands = args->commands;
	env_t *head = args->environment, *node;

	if (check_args(args, 3) == 0)
	{
		node = check_env(args, commands[1]);
		if (node == NULL)
		{
			/* add new node */
			add_env_node(&head, commands[1], commands[2], args);
		}
		else
		{
			free(node->val);
			node->val = commands[2];
		}
		re_init_env(args);
	}
	else
	{
		_dprintf(2, "%s: Usage: setenv VARIABLE VALUE\n", args->exe);
		args->exit = 1;
	}
	args->exit = 0;
	return (0);
}

/**
 * un_set_env - removes a node from the environment variable of the shell
 * @args: arguments structure
 *
 * Return: always 0
 */
int un_set_env(arg_t *args)
{
	char **commands = args->commands;
	env_t *head = args->environment, *node;

	if (check_args(args, 2) == 0)
	{
		if (check_env(args, commands[1]) != NULL)
		{
			/* remove node */
			if (strcmp(head->var, commands[1]) == 0)
			{
				args->environment = head->next;
				free(head->var);
				free(head->val);
				free(head);
			}
			else
				while (head->next != NULL)
				{
					node = head->next;
					if (strcmp(node->var, commands[1]) == 0)
					{
						head->next = node->next;
						free(node->var);
						free(node->val);
						free(node);
						break;
					}
					head = head->next;
				}
			re_init_env(args);
		}
		else
		{
			_dprintf(2, "%s: %s: No such variable\n", args->exe, commands[1]);
			args->exit = 1;
		}
	}
	else
	{
		_dprintf(2, "%s: Usage: unsetenv VARIABLE\n", args->exe);
		args->exit = 1;
	}
	args->exit = 0;
	return (0);
}

/**
 * change_dir - changes the current working directory
 * @args: arguments structure
 *
 * Return: always 0
 */
int change_dir(arg_t *args)
{
	int ret;
	char **commands = args->commands, *directory = commands[1], *oldpwd;
	char *exe = args->exe, *pwd;
	env_t *node;

	if (get_args_num(args) > 2)
	{
		_dprintf(2, "%s: %s: too many arguments\n", args->exe, commands[0]);
		args->exit = errno;
		return (0);
	}
	if (directory == NULL)
		directory = get_env_variable(args, "HOME");
	else if (strcmp(directory, "-") ==  0)
		directory = get_env_variable(args, "OLDPWD");
	oldpwd = getcwd(NULL, 0);
	ret = chdir(directory);
	if (ret == -1)
	{
		_dprintf(2, "%s: %s: cannot access %s\n", exe, commands[0], commands[1]);
		args->exit = errno;
		free(oldpwd);
		return (0);
	}
	pwd = getcwd(NULL, 0);
	node = check_env(args, "PWD");
	free(node->val);
	node->val = pwd;
	node = check_env(args, "OLDPWD");
	free(node->val);
	node->val =  oldpwd;
	re_init_env(args);
	args->exit = 0;
	return (0);
}