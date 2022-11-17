#include "main.h"
#include <stdarg.h>

/**
 * _realoc - reallocates memory for a buffer
 * @old: old buffer
 * @size: size of the new buffer
 * @new: new character to be added
 *
 * Return: new buffer created
 */
char *_realoc(char *old, int size, char new)
{
	int i;
	char *new_string;

	new_string = (char *)malloc(sizeof(char) * (size + 1));
	if (new_string == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < (size - 1); i++)
		new_string[i] = old[i];
	new_string[i] = new;
	new_string[size] = '\0';
	free(old);
	return (new_string);
}

/**
 * decode_string - prints a string
 * @valist: va_list object
 * @buff: buffer to write to
 * @n: number of characters in the buffer
 *
 * Return: void
 */
void decode_string(va_list valist, char **buff, int *n)
{
	int i;
	char *str = va_arg(valist, char *), *new_buffer = *buff;

	if (str == NULL)
	{
		write(2, "Wrong use of _dprintf", 21);
		exit(EXIT_FAILURE);
	}
	for (i = 0; str[i] != '\0'; i++)
	{
		*n += 1;
		new_buffer = _realoc(new_buffer, *n, str[i]);
	}
	*buff = new_buffer;
}

/**
 * get_spec_func - returns function associated with specifier
 * @c: character associated with specifier
 *
 * Return: pointer to the function to be called otherwise NULL
 */
void (*get_spec_func(char c))(va_list, char **, int *)
{
	int i;
	spec_t con_spec[] = {
		{'s', decode_string},
		{'\0', NULL}
	};

	for (i = 0; con_spec[i].fmt != '\0'; i++)
		if (c == con_spec[i].fmt)
			return (con_spec[i].func);
	return (NULL);
}

/**
 * _dprintf - writes a buffer to specified file descriptor
 * @fd: file descriptor to write to
 * @format: format of string to be written to file descriptor
 *
 * Return: number of characters written
 */
int _dprintf(int fd, const char *format, ...)
{
	int i, n;
	char *buff = NULL;
	void (*op_func)(va_list, char **, int *);
	va_list args;

	if (format == NULL)
		return (-1);
	i = n = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == '\0')
			return (-1);
		else if (format[i] == '%' && format[i + 1] != '%')
		{
			op_func = get_spec_func(format[i + 1]);
			if (op_func)
				op_func(args, &buff, &n);
			i += 2;
		}
		else if (format[i] == '%' && format[i + 1] == '%')
		{
			i += 2;
			n++;
			buff = _realoc(buff, n, '%');
		}
		else
		{
			n++;
			buff = _realoc(buff, n, format[i]);
			i++;
		}
	}
	write(fd, buff, n);
	free(buff);
	return (n);
}
