#include "main.h"

/**
 * get_args_num - gets the number of arguments
 * @args: arguments structure
 *
 * Return: number of arguments
 */
int get_args_num(arg_t *args)
{
	int i, count;
	char **commands = args->commands;

	for (i = 0, count = 0; commands[i] != NULL; i++)
		count++;
	return (count);
}

/**
 * check_args - checks if the correct number of arguments are passed to the
 * function
 * @args: arguments structure
 * @n: number of arguments to be checked for
 *
 * Return: 1 if false and 0 if true
 */
int check_args(arg_t *args, int n)
{
	if (get_args_num(args) != n)
		return (1);
	return (0);
}

/**
 * check_env - checks if a variable exists
 * @args: arguments structure
 * @variable: variable to be located
 *
 * Return: pointer to variable
 */
env_t *check_env(arg_t *args, char *variable)
{
	env_t *environment = args->environment;
	char *var;

	while (environment != NULL)
	{
		var = environment->var;
		if (strcmp(var, variable) == 0)
			return (environment);
		environment = environment->next;
	}
	return (NULL);
}

/**
 * re_init_env - reinitializes the environment variable
 * @args: argument structure
 *
 * Return: void
 */
void re_init_env(arg_t *args)
{
	int n = 1;
	char **_environ = NULL, *temp, **temp1, *val;
	env_t *head = args->environment;

	while (head != NULL)
	{
		temp = _strcat(head->var, "=");
		val = _strcat(temp, head->val);
		_environ = _realloc(_environ, n, val);
		free(temp);
		free(val);
		n++;
		head = head->next;
	}
	_environ = _realloc(_environ, n, NULL);
	temp1 = args->_environ;
	for (n = 0; temp1[n] != NULL; n++)
		free(temp1[n]);
	free(args->_environ);
	args->_environ = _environ;
}

/**
 * get_env_variable - returns the value of an environment variable
 * @args: arguments structure
 * @var: name of the variable
 *
 * Return: the value of an environment variab;e
 */
char *get_env_variable(arg_t *args, char *var)
{
	env_t *head = args->environment;

	while (head != NULL)
	{
		if (strcmp(var, head->var) == 0)
			return (head->val);
		head = head->next;
	}
	return (NULL);
}
