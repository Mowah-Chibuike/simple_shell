#include "main.h"
#include <dirent.h>

/**
 * file_search - searches for a file in a list of directories
 * @args: arguments structure
 *
 * Return: file pathname
 */
char *file_search(arg_t *args)
{
	char *file = NULL, *directory, *pathname = NULL, *check;
	DIR *dir;
	list_t *temp = args->path;
	struct dirent *content;

	while (temp != NULL)
	{
		dir = opendir(temp->directory);
		if (dir == NULL)
			continue;
		errno = 0;
		content = readdir(dir);
		while (content != NULL)
		{
			file = content->d_name;
			if (_strcmp(file, args->command) == 0)
			{
				check = _strdup(temp->directory);
				directory = _strcat(check, "/");
				pathname = _strcat(directory, file);
				free(check);
				free(directory);
				closedir(dir);
				return (pathname);
			}
			content = readdir(dir);
		}
		closedir(dir);
		temp = temp->next;
	}
	return (NULL);
}

/**
 * search_path - searches path for a file
 * @args:  argument structure
 *
 * Return: void
 */
char *search_path(arg_t *args)
{
	char *text = NULL;
	char **commands;

	if (access(args->command, F_OK) != 0)
	{
		text = file_search(args);
		if (text != NULL)
		{
			commands = copy_string_array(args->commands);
			free_strings_array(args->commands);
			free(commands[0]);
			commands[0] = text;
			args->command = text;
			args->commands = commands;
		}
	}
	return (text);
}



