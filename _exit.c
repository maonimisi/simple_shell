#include "shell.h"
/**
 * _strncpy - Function copies a string
 * @destination: The destination string to be copied to
 * @source: The source string to copy
 * @max_len: The maximum number of characters to be copied
 * Return: Return pointer to the destination string
 */
char *_strncpy(char *destination, char *source, int max_len)
{
	int i, j;
	char *result = destination;

	i = 0;
	while (source[i] != '\0' && i < max_len - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < max_len)
	{
		j = i;
		while (j < max_len)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 * _strncat - Function concatenates two strings
 * @destination: The first string
 * @source: The second string
 * @max_len: The maximum number of bytes to be used
 * Return: Return pointer to the concatenated string
 */
char *_strncat(char *destination, char *source, int max_len)
{
	int i, j;
	char *result = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < max_len)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < max_len)
		destination[i] = '\0';

	return (result);
}

/**
 * _strchr - Function locates a character in a string
 * @str: The string to be parsed
 * @character: The character to look for
 * Return: Return a pointer to the first occurrence of the
 *	character in the string,or NULL if the character is not found
 */
char *_strchr(char *str, char character)
{
	do {
		if (*str == character)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
