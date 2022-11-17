#include <stdio.h>

/**
 * check_string - checks if string can be converted to an integer
 * @str: string to be checked
 *
 * Return: 1 if true and 0 if false
 */
int check_string(char *str)
{
	int i, len;

	len = 0;
	for (i = 0; str[i] != '\0'; i++)
		len++;

	for (i = 0; i < len; i++)
	{
		if (str[i] != '-')
		{
			if ((str[i] < '0' || str[i] > '9'))
				return (0);
		}
		else
		{
			if (str[i + 1] == '\0')
				return (0);
			if ((str[i + 1] < '0' || str[i] > '9') && i < len - 1)
				return (0);
		}
	}
	return (1);
}


/**
 * _atoi - converts a strng to an integer
 * @str: string to be coverted
 *
 * Return: the integer value of the string
 */
int _atoi(char *str)
{
	int len, i, digit, flag, num;

	for (i = 0, len = 0; str[i] != '\0'; i++)
		len++;
	i = digit = num = flag = 0;
	while (i < len)
	{
		/* cheeck if negative integer */
		if (str[0] == '-')
			flag = 1;
		if (str[i] >= '0' && str[i] <= '9')
		{
			digit = str[i] - '0';
			if (flag)
				digit = -digit;
		}
		num = num * 10 + digit;
		if ((str[i + 1] < '0' || str[i + 1] > '9') && i != (len - 1))
			return (0);
		i++;
	}
	return (num);
}
