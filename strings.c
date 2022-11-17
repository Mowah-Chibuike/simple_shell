#include "main.h"

/**
 * _strlen - finds the length of a string
 * @str: string to find the length
 *
 * Return: length of the string
 */
int _strlen(const char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: the difference between the ascii values pf the first non-equal
 * characters in the stringd
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0, res = 0;

	while (i >= 0)
	{
		res = s1[i] - s2[i];
		if (res != 0)
			break;
		if ((s1[i] == '\0') || (s2[i] == '\0'))
			break;
		i++;
	}
	return (res);
}

/**
 * _strdup - duplicates a string
 * @str: string to be duplicated
 *
 * Return: pointer to str duplicate
 */
char *_strdup(char *str)
{
	int len, i;
	char *new_string;

	if (str == NULL)
		return (NULL);
	len = _strlen(str);
	new_string = (char *)malloc((len + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		new_string[i] = str[i];
	new_string[i] = '\0';
	return (new_string);
}

/**
 * copy_string_array - copies an array of strings to a new location
 * @main: arrays of strings to copy
 *
 * Return: the newly created array of strings
 */
char **copy_string_array(char **main)
{
	int i;
	char **new_array = NULL;

	if (main == NULL)
		return (NULL);
	for (i = 1; main[i - 1] != NULL; i++)
		new_array = _realloc(new_array, i, main[i - 1]);
	new_array = _realloc(new_array, i, NULL);
	return (new_array);
}
