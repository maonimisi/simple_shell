#include "shell.h"

/**
 * _getEnvironmentStrings - Function returns a copy of the environment strings
 * @info: Structure containing arguments
 * Return: Return pointer to the array of environment strings
 */
char **_getEnvironmentStrings(info_t *info)
{
	if (!info->environ || info->_changedEnvp)
	{
		info->environ = _listToStringArray(info->_envp);
		info->_changedEnvp = 0;
	}

	return (info->environ);
}

/**
 * _unsetEnvironmentVariable - Function remove an environment variable
 * @info: Structure containing potential arguments.
 * @variable: The variable to unset
 * Return: 1 if variable was deleted, else  0 otherwise.
 */
int _unsetEnvironmentVariable(info_t *info, char *variable)
{
	list_t *node = info->_envp;
	size_t index = 0;
	char *p;

	if (!node || !variable)
		return (0);

	while (node)
	{
		p = _startsWith(node->str, variable);
		if (p && *p == '=')
		{
			info->_changedEnvp = _deleteNodeAtIndex(&(info->_envp), index);
			index = 0;
			node = info->_envp;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->_changedEnvp);
}

/**
 * _setEnvironmentVariable - Function Initialize a new env. var or modify an
 * existin 1
 * @info: Structure containing arguments
 * @variable: The variable to set or modify.
 * @value: The value to assign to the variable
 * Return: Always 0
 */
int _setEnvironmentVariable(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->_envp;
	while (node)
	{
		p = _startsWith(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->_changedEnvp = 1;
			return (0);
		}
		node = node->next;
	}
	_addNodeEnd(&(info->_envp), buffer, 0);
	free(buffer);
	info->_changedEnvp = 1;
	return (0);
}
