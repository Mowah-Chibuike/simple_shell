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
