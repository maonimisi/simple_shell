#include "shell.h"
/**
 * _splitString - Function splits a string into words based on a delimiter
 * @str: The input string
 * @delim: The delimiter string
 * Return: Return a pointer to an array of strings, or NULL on failure
 */
char **_splitString(char *str, char *delim)
{
	int i, j, k, m, num_words = 0;
	char **result;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_isDelimeter(str[i], delim) && (_isDelimeter(str[i + 1], delim) ||
			!str[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	result = malloc((1 + num_words) * sizeof(char *));
	if (!result)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (_isDelimeter(str[i], delim))
			i++;
		k = 0;
		while (!_isDelimeter(str[i + k], delim) && str[i + k])
			k++;
		result[j] = malloc((k + 1) * sizeof(char));
		if (!result[j])
		{
			for (k = 0; k < j; k++)
				free(result[k]);
			free(result);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			result[j][m] = str[i++];
		result[j][m] = '\0';
	}
	result[j] = NULL;
	return (result);
}

/**
 * _splitStringBySingleDelim - splits string into words based on a single delim
 * @str: The input string
 * @delim: The delimiter
 * Return: Return a pointer to an array of strings, or NULL on failure
 */
char **_splitStringBySingleDelim(char *str, char delim)
{
	int i, j, k, m, num_words = 0;
	char **result;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
		    (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			num_words++;
	if (num_words == 0)
		return (NULL);
	result = malloc((1 + num_words) * sizeof(char *));
	if (!result)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;
		k = 0;
		while (str[i + k] != delim && str[i + k] && str[i + k] != delim)
			k++;
		result[j] = malloc((k + 1) * sizeof(char));
		if (!result[j])
		{
			for (k = 0; k < j; k++)
				free(result[k]);
			free(result);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			result[j][m] = str[i++];
		result[j][m] = '\0';
	}
	result[j] = NULL;
	return (result);
}
