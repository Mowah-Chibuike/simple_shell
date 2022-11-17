#include "main.h"
#include <stdlib.h>

/**
 * _realloc - reallocates memory for a new string in an array of strings
 * @old: old list of strings
 * @size: size of new array
 * @str: new string to be added
 *
 * Return: new array of string created
 */
char **_realloc(char **old, int size, char *str)
{
	int i;
	char **new_list, *new_string;

	new_list = (char **)malloc(sizeof(char *) * size);
	new_string = _strdup(str);
	if (new_list == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < (size - 1); i++)
		new_list[i] = old[i];
	new_list[i] = new_string;
	free(old);
	return (new_list);
}

/**
 * _strcat - concatenates two strings
 * @str1: string1
 * @str2: string2
 *
 * Return: pointer to new string allocated
 */
char *_strcat(char *str1, char *str2)
{
	int i, j, len1, len2;
	char *new_string;

	len1 = _strlen((str1));
	len2 = _strlen(str2);
	new_string = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (new_string == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < len1; i++)
		new_string[i] = str1[i];
	for (j = 0; j < len2; i++, j++)
		new_string[i] = str2[j];
	new_string[i] = '\0';
	return (new_string);
}
