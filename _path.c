#include "shell.h"

/**
 * _isExecutableCommand - determines if a file is an executable command
 * @info: he info struct
 * @path: Path to the file
 * Return: Return 1 if true, 0 otherwise
 */
int _isExecutableCommand(info_t *info, char *path)
{
	struct stat file_stat;

	(void)info;
	if (!path || stat(path, &file_stat))
		return (0);

	if (file_stat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _duplicateCharacters - Function duplicates characters
 * @source: The source string
 * @start: Starting index
 * @end: Ending index
 * Return: pointer to new buffer
 */
char *_duplicateCharacters(char *source, int start, int end)
{
	static char buffer[1024];
	int i = 0, j = 0;

	for (j = 0, i = start; i < end; i++)
		if (source[i] != ':')
			buffer[j++] = source[i];
	buffer[j] = '\0';
	return (buffer);
}

/**
 * _findCommandPath - Finds the full path of a command in the PATH string
 * @info: The info struct
 * @path_string: The PATH string
 * @command: The command to find
 * Return: full path of the command if found, or NULL
 */
char *_findCommandPath(info_t *info, char *path_string, char *command)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((_strlen(command) > 2) && _startsWith(command, "./"))
	{
		if (_isExecutableCommand(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			path = _duplicateCharacters(path_string, curr_pos, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (_isExecutableCommand(info, path))
				return (path);
			if (!path_string[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
