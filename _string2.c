#include "shell.h"
/**
* _strcpy - copy the string pointed to by src to dest
* @dest: string to replace
* @src: string to copy
* Return: Return dest
*/
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strdup - returns a pointer to a newly allocated memory space
 * @str: the source string
 * Return: returns a pointer to the duplicate memory
 */

char *_strdup(const char *str)
{
	int i, len = 0;
	char *copy;

	if (str == 0)
	{
		return (NULL);
	}
	while (str[len] != '\0')
	{
		len++;
	}

	copy = malloc(sizeof(char) * (len + 1));

	if (copy == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < len; i++)
		copy[i] = str[i];
	copy[len] = '\0';
	return (copy);
}

/**
* _puts - this function prints a new line to stdout
* @str: the character to be printed
* Return: Always 0.
*/
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
