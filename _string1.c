#include "shell.h"
/**
* _strlen - this function return the lenght of a string
* @s: the string to be checked
* Return: Always 0.
*/
int _strlen(char *s)
{
	int len;
	int i;

	i = 0, len = 0;
	while (s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

/**
* *_strcat - this function concatenate two strings
* @dest: first string
* @src: second string
* Return: Address of dest.
*/
char *_strcat(char *dest, char *src)
{
	int i = 0;
	int j = 0;

	while (dest[i] != '\0')
	{
		i++;
	}
		while (src[j] != '\0')
		{
			dest[i] = src[j];
			i++;
			j++;
		}
		dest[i] = '\0';
	return (dest);
}

/**
* _strcmp - compare two strings.
* @s1: string one
* @s2: string two
* Return: integer number
*/
int _strcmp(char *s1, char *s2)
{
	int i = 0, com = 0;

	while (s1[i] != '\0' && s2[i] != '\0' && com == 0)
	{
		com = s1[i] - s2[i];
		i++;
	}
	return (com);
}

/**
 * _startsWith - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 * Return: address of next char of haystack or NULL
 */
char *_startsWith(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
