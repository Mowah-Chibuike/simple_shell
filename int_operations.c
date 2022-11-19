#include "main.h"

/**
 * _pow - raises a number by another number
 * @x: the base
 * @y: the power
 *
 * Return: exponent
 */
int _pow(int x, int y)
{
	int res, i;

	res = x;
	for (i = 1; i < y; i++)
		res *= x;
	return (res);
}
