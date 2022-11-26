#include "main.h"

/**
 * reset - sets all characters in a buffer to the NULL byte
 * @str: newly allocated memory to be reset
 */
void reset(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		str[i] = '\0';
}

/**
 * check_for_newline - checks a buffer for the newline character
 * @str: buffer to be checked
 * @num_chars: number of characters checked
 * @line_ptr: buffer holding characters
 *
 * Return: 1 if newline character is found, otherwise 0
 */
int check_for_newline(char *str, ssize_t *num_chars, char **lineptr)
{
	int i;

	for (i = 1; i < 64; i++)
	{
		*lineptr = _realoc(*lineptr, i, str[i - 1]);
		*num_chars += 1;
		if (str[i - 1] == '\n')
		{
			return (1);
		}
	}
	return (0);
}

/**
 * _getline - gets a line from an open file
 * @line_ptr: location to send the line found to
 * @fd: file descriptor of the open file
 *
 * Return: Number of characters in the found line othersise -1
 */
ssize_t _getline(char **lineptr, int fd)
{
	static int current = 0;
	ssize_t rd = 0;
	char read_chars[64];
	static ssize_t seek = 0;

	if (*lineptr != NULL)
		reset(*lineptr);
	if (current != fd)
	{
		seek = 0;
		current = fd;
	}
	lseek(fd, seek, SEEK_SET);
	rd = read(fd, read_chars, 64);
	if (rd == -1)
		perror("Error");
	if (rd == 0)
		return (-1);
	while (check_for_newline(read_chars, &seek, lineptr) != 1)
	{
		lseek(fd, seek, SEEK_SET);
		rd = read(fd, read_chars, 63);
		if (rd == 0)
		{
			perror("Error");
			seek = -1;
			break;
		}
	}
	return (seek);
}
/*
int main(int argc, char *argv[])
{
	char *line = NULL;

	(void)argv;
	if (argc < 2)
	{
		write(2, "Wrong Number of Args\n", 22);
		return (1);
	}
	_getline(&line, STDIN_FILENO);
	printf("%s", line);
	free(line);
	return (0);
}*/
