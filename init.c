#include "main.h"

/**
 * get_env - sets the environment variable
 * @args: arguments structure
 *
 * Return: void
 */
void get_env(arg_t *args)
{
	int i;
	char *var, *val, *environment;
	env_t *head = NULL;

	for (i = 0; environ[i] != NULL; i++)
	{
		environment = _strdup(environ[i]);
		var = strtok(environment, "=");
		val = strtok(NULL, "");
		add_env_node(&head, var, val, args);
		free(environment);
	}
	args->environment = head;
}

/**
 * get_path_string - gets the value of the PATH variable
 * @args: argument structure
 *
 * Return: the value of the PATH variable
 */
void get_path_string(arg_t *args)
{
	char *var, *val = NULL;
	env_t *head = args->environment;

	while (head != NULL)
	{
		var = head->var;
		if (strcmp(var, "PATH") == 0)
			val = head->val;
		head = head->next;
	}
	args->pathstring = val;
}

/**
 * get_path_directories - gets the directories in the PATH variable
 * @args: argument structure
 *
 * Return: a linked list containing every directory in hte PATH
 */
void get_path_directories(arg_t *args)
{
	list_t *head = NULL;
	char *path = _strdup(args->pathstring);
	char *token;

	if (path == NULL)
	{
		args->path = NULL;
		return;
	}
	token = strtok(path, ":");
	while (token != NULL)
	{
		add_list_node(&head, token, args);
		token = strtok(NULL, ":");
	}
	args->path = head;
	free(path);
}

/**
 * init_env - initializes the environment structure of the arguments structure
 * @args: arguments structure
 *
 * Return: void
 */
void init_env(arg_t *args)
{
	int i, n;
	char **env = NULL;

	(void)env;
	(void)args;
	for (i = 0, n = 1; environ[i] != NULL; i++, n++)
		env = _realloc(env, n, environ[i]);
	env = _realloc(env, n, environ[i]);
	args->_environ = env;
}

/**
 * shell_init - initializes shell variables
 *
 * Return: initialized shell variables
 */
arg_t *shell_init(void)
{
	arg_t *args;

	args = (arg_t *)malloc(sizeof(arg_t));
	if (args == NULL)
		return (NULL);
	get_env(args);
	get_path_string(args);
	get_path_directories(args);
	init_env(args);
	args->exit_status = args->exit = 0;
	return (args);
}
