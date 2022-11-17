#ifndef STRUCTS
#define STRUCTS

/**
 * struct op - Struct op
 * @fmt: format of the specifier
 * @func: function associated with the specifier
 */
typedef struct op
{
	char fmt;
	void (*func)(va_list, char **, int *);
} spec_t;

/**
 * struct list - struct list
 * @directory: directory path
 * @next: pointer to next node
 *
 * Description: linked list of strings
 */
typedef struct list
{
	char *directory;
	struct list *next;
} list_t;

/**
 * struct env - holds the environment variables and their values
 * @var: environment variable
 * @val: value of the environment variable
 * @next: pointer  to the next environment variable
 */
typedef struct env
{
	char *var;
	char *val;
	struct env *next;
} env_t;

/**
 * struct arguments - holds everything that should be passed down to other
 * functions
 * @exe: holds the name of the binary file that will launch the shell
 * @command: holds the command passed to the shell to be executed
 * @commands: holds the arguments for the command passed to the shell
 * @environment: the environment of the shell
 * @pathstring: the value of the PATH variable
 * @path: linked list holding the directories in the PATH variable
 * @exit: 0 if program should exit and 1 if program should not
 */
typedef struct arguments
{
	char *exe;
	char *command;
	char **commands;
	char **_environ;
	env_t *environment;
	char *pathstring;
	list_t *path;
	int exit;
	int exit_status;
} arg_t;

/**
 * struct builtins - holds a builtin function and the command associated with
 * it
 * @command: name of the command
 * @builtin: function to be called
 */
typedef struct builtins
{
	char *command;
	int (*builtin)(arg_t *);
} builtins_t;

/**
 * struct coms - a linked lists storing all commands seperated by operators
 * @commands: array containing commands and their arguments
 * @operator: the operator to be used
 * @next: next node of the linked list
 */
typedef struct coms
{
	char **commands;
	char *operator;
	struct coms *next;
} coms_t;

#endif /* STRUCT */
