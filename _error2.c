#include "shell.h"
/**
 * _erratoi - Function converts a string to an integer
 * @str: The string to be converted
 * Return: Return 0 if no numbers in the string, converted number otherwise
 *         -1 on error
 */
int _erratoi(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;

	for (index = 0; str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (result);
}

/**
 * _printDecimal - Function  prints a decimal (integer) number (base 10)
 * @input: The input number
 * @fd: The file descriptor to write to
 * Return: Return number of characters printed
 */
int _printDecimal(int input, int fd)
{
	int (*putchar_func)(char) = _putchar;
	int i, count = 0;
	unsigned int abs_val, current;

	if (fd == STDERR_FILENO)
		putchar_func = _eputchar;
	if (input < 0)
	{
		abs_val = -input;
		putchar_func('-');
		count++;
	}
	else
		abs_val = input;
	current = abs_val;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_val / i)
		{
			putchar_func('0' + current / i);
			count++;
		}
		current %= i;
	}
	putchar_func('0' + current);
	count++;
	return (count);
}
/**
 * _printError - Function prints an error messages
 * @info: The parameter and return info struct
 * @error_type: The string containing the specified error type
 * Return: Void
 */
void _printError(info_t *info, char *error_type)
{
	_eputs(info->_filename);
	_eputs(": ");
	_printDecimal(info->_lineCount, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->_argv[0]);
	_eputs(": ");
	_eputs(error_type);
}

/**
 * _removeComments - Function replaces the first instance of '#' with '\0'
 * @buf: Address of the string to modify
 * Return: Void
 */
void _removeComments(char *buf)
{
	int index;

	for (index = 0; buf[index] != '\0'; index++)
		if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
}

/**
 * _convertNumber - Function converter, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *_convertNumber(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
