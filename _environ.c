#include "shell.h"
/**
 * _myEnv - Function prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int _myEnv(info_t *info)
{
	_printListStr(info->_envp);
	return (0);
}

/**
 * _getEnv - Function  gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: Environment variable name
 * Return: Return value of the environment variable
 */
char *_getEnv(info_t *info, const char *name)
{
	list_t *node = info->_envp;
	char *env_str;

	while (node)
	{
		env_str = _startsWith(node->str, name);
		if (env_str && *env_str)
			return (env_str);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mySetEnv - Function initialize a new environment variable,
 *              or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int _mySetEnv(info_t *info)
{
	if (info->_argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setEnv(info, info->_argv[1], info->_argv[2]))
		return (0);
	return (1);
}

/**
 * _myUnsetEnv - Function remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int _myUnsetEnv(info_t *info)
{
	int i;

	if (info->_argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i < info->_argc; i++)
		_unSetEnv(info, info->_argv[i]);

	return (0);
}

/**
 * _populateEnvList - Function populates the environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int _populateEnvList(info_t *info)
{
	list_t *env_node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_addNodeEnd(&env_node, environ[i], 0);
	info->_envp = env_node;
	return (0);
}
