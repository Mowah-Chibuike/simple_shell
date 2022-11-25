#include "main.h"

/**
 * set_pwd - sets the PWD and OLDPWD of the environment
 * @args: argument structure
 * @oldpwd: oldpwd of the calling process
 */
void set_pwd(arg_t *args, char *oldpwd)
{
	char *pwd;
	env_t *node;

	pwd = getcwd(NULL, 0);
	node = check_env(args, "PWD");
	free(node->val);
	node->val = pwd;
	node = check_env(args, "OLDPWD");
	if (node != NULL)
	{
		free(node->val);
		node->val = _strdup(oldpwd);
	}
	re_init_env(args);
	free(oldpwd);
	args->exit = args->exit_status = 0;
}

/**
 * get_varname - gets the variable name
 * @str: string to be checked
 *
 * Return: variable name
 */
char *get_varname(char *str)
{
	int i;
	char *var = NULL;

	for (i = 1; str[i] != '\0'; i++)
		var = _realoc(var, i, str[i]);
	return (var);
}

/**
 * convert_num_to_string - converts an integer to a string
 * @num: num to be converted
 *
 * Return: converted number
 */
char *convert_num_to_string(int num)
{
	int i, exp, res[10], sum, n = 0;
	char *new_buffer = NULL;

	exp = _pow(10, 9);
	res[0] = num / exp;
	for (i = 1; i < 9; i++)
		res[i] = (num / (exp / _pow(10, i))) % 10;
	res[i] = num % 10;
	sum = 0;
	for (i = 0; i < 10; i++)
	{
		sum += res[i];
		if (sum > 0 || i == 9)
		{
			n += 1;
			new_buffer = _realoc(new_buffer, n, (res[i] + '0'));
		}
	}
	return (new_buffer);
}

/**
 * check_defaults - checks for predefined variables
 * @str: string to be checked
 *
 * Return: 1 if predefined variable, otherwise 0
 */
char *check_defaults(arg_t *args, char *str)
{
	char *num_string = NULL;

	if (str[1] == '$' && str[2] == '\0')
		num_string = convert_num_to_string(args->shell_pid);
	if (str[1] == '?' && str[2] == '\0')
		num_string = convert_num_to_string(args->exit_status);
	return (num_string);
}

/**
 * check_for_variables - handles variables expansion
 * @args: arguments structure
 */
void check_for_variables(arg_t *args)
{
	int i;
	char *new_command = NULL, *var;

	for (i = 0; args->commands[i] != NULL; i++)
	{
		if (args->commands[i][0] == '$' && args->commands[i][1] != '\0')
		{
			new_command = check_defaults(args, args->commands[i]);
			if (new_command == NULL)
			{
				var = get_varname(args->commands[i]);
				new_command = get_env_variable(args, var);
				if (new_command != NULL)
				{
					free(args->commands[i]);
					args->commands[i] = _strdup(new_command);
				}
				else
				{
					free(args->commands[i]);
					args->commands[i] = NULL;
				}
				free(var);
			}
			else
			{
				free(args->commands[i]);
				args->commands[i] = new_command;
			}
		}
	}
}
