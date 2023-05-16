#include "shell.h"
/**
 * _isInteractive - Function check if shell is interactive mode
 * @info: Pointer to the info struct
 * Return: 1 if in interactive mode,else return  0 if otherwise
 */
int _isInteractive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->_readFileDescriptor <= 2);
}

/**
 *_isDelimeter - Function check if a character is a delimiter
 * @c: The character to check
 * @delimeter: The delimiter string
 * Return: 1 if true, else return 0 if otherwise
 */
int _isDelimeter(char c, char *delimeter)
{
	while (*delimeter)
	{
		if (*delimeter++ == c)
			return (1);
	}
	return (0);
}

/**
 * _isAlpha - Function checks for an alphabetic character
 * @c: The character to check
 * Return: 1 if character is alphabetic, else 0 if otherwise
 */
int _isAlpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Function converts a string to an integer
 * @s: The string to be converted
 * Return: 0 if no numbers in the string, converted number otherwise
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
