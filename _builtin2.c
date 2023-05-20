#include "shell.h"

/**
 * _myHistory - Fuction displays the history list, one command by line,
 *              preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype
 * Return: Always 0
 */
int _myHistory(info_t *info)
{
	_printList(info->_history);
	return (0);
}

/**
 * _unsetAlias - Function removes an alias from the alias list
 * @info: Parameter struct
 * @alias_str: The alias string to be unset
 * Return: Always 0 on success, else 1 otherwise
 */
int _unsetAlias(info_t *info, char *alias_str)
{
	char *equal_sign, temp_char;
	int ret;

	equal_sign = _strchr(alias_str, '=');
	if (!equal_sign)
		return (1);
	temp_char = *equal_sign;
	*equal_sign = '\0';
	ret = _deleteNodeAtIndex(&(info->_alias),
		_getNodeIndex(info->_alias, _nodeStartsWith(info->_alias, alias_str, -1)));
	*equal_sign = temp_char;
	return (ret);
}

/**
 * _setAlias - Function sets an alias in the alias list
 * @info: Parameter struct
 * @alias_str: The alias string to be set
 * Return: Always 0 on success, else 1 otherwise
 */
int _setAlias(info_t *info, char *alias_str)
{
	char *equal_sign;

	equal_sign = _strchr(alias_str, '=');
	if (!equal_sign)
		return (1);
	if (!*++equal_sign)
		return (_unsetAlias(info, alias_str));

	_unsetAlias(info, alias_str);
	return (_addNodeEnd(&(info->_alias), alias_str, 0) == NULL);
}

/**
 * _printAlias - prints an alias string
 * @alias_node: the alias node
 * Return: Always 0 on success, else 1 otherwise
 */
int _printAlias(list_t *alias_node)
{
	char *equal_sign = NULL, *alias_str = NULL;

	if (alias_node)
	{
		equal_sign = _strchr(alias_node->str, '=');
		for (alias_str = alias_node->str; alias_str <= equal_sign; alias_str++)
			_putchar(*alias_str);
		_putchar('\'');
		_puts(equal_sign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myAlias - Function mimics the alias builtin
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myAlias(info_t *info)
{
	int i = 0;
	char *equal_sign = NULL;
	list_t *alias_node = NULL;

	if (info->_argc == 1)
	{
		alias_node = info->_alias;
		while (alias_node)
		{
			_printAlias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}

	for (i = 1; info->_argv[i]; i++)
	{
		equal_sign = _strchr(info->_argv[i], '=');
		if (equal_sign)
			_setAlias(info, info->_argv[i]);
		else
			_printAlias(_nodeStartsWith(info->_alias, info->_argv[i], '='));
	}

	return (0);
}
