#include "shell.h"
/**
 * _eputchar - Function writes character c to stderr
 * @c: The character to printed
 * Return: On success 1, on error, -1 is returned,
 * and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int buffer_index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(2, buffer, buffer_index);
		buffer_index = 0;
	}

	if (c != BUF_FLUSH)
		buffer[buffer_index++] = c;

	return (1);
}
/**
 * _eputs - Function prints a string to stderr
 * @str: The string to be printed
 * Return: Void
 */
void _eputs(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		_eputchar(str[index]);
		index++;
	}
}


/**
 * _putFileDescriptor - Function writes the character c to the given fd
 * @c: The character to be printed
 * @fileDescriptor: The file descriptor to write to
 * Return: On success 1, on error, -1 is returned, and errno is set
 * appropriately.
 */
int _putFileDescriptor(char c, int fileDescriptor)
{
	static int buffer_index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(fileDescriptor, buffer, buffer_index);
		buffer_index = 0;
	}

	if (c != BUF_FLUSH)
		buffer[buffer_index++] = c;

	return (1);
}

/**
 * _putsFileDescriptor - prints a string to the given file descriptor
 * @str: The string to be printed
 * @fileDescriptor: The file descriptor to write to
 * Return: Return the number of characters put
 */
int _putsFileDescriptor(char *str, int fileDescriptor)
{
	int count = 0;

	if (!str)
		return (0);

	while (*str)
	{
		count += _putFileDescriptor(*str++, fileDescriptor);
	}

	return (count);
}
