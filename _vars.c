#include "shell.h"

/**
 * _isChainDelimiter - test if the current character in the buffer is a chain
 * delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of the current position in buf
 * Return: 1 if chain delimiter, 0 otherwise
 */
int _isChainDelimiter(info_t *info, char *buf, size_t *p)
{
	size_t current_pos = *p;

	if (buf[current_pos] == '|' && buf[current_pos + 1] == '|')
	{
		buf[current_pos] = '\0';
		current_pos++;
		info->_commandBufferType = CMD_OR;
	}
	else if (buf[current_pos] == '&' && buf[current_pos + 1] == '&')
	{
		buf[current_pos] = '\0';
		current_pos++;
		info->_commandBufferType = CMD_AND;
	}
	else if (buf[current_pos] == ';')
	{
		buf[current_pos] = '\0';
		info->_commandBufferType = CMD_CHAIN;
	}
	else
		return (0);

	*p = current_pos;
	return (1);
}

/**
 * _checkChainContinuation - checks if we should continue chaining based
 * on the last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of the current position in buffer
 * @start_pos: starting position in buffer
 * @buf_len: length of buffer
 * Return: Void
 */
void _checkChainContinuation(info_t *info, char *buf, size_t *p, size_t
				start_pos, size_t buf_len)
{
	size_t current_pos = *p;

	if (info->_commandBufferType == CMD_AND)
	{
		if (info->status)
		{
			buf[start_pos] = '\0';
			current_pos = buf_len;
		}
	}
	if (info->_commandBufferType == CMD_OR)
	{
		if (!info->_status)
		{
			buf[start_pos] = '\0';
			current_pos = buf_len;
		}
	}

	*p = current_pos;
}

/**
 * _replaceAlias - replaces an alias in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int _replaceAlias(info_t *info)
{
	int i;
	list_t *alias_node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		alias_node = _nodeStartsWith(info->alias, info->argv[0], '=');
		if (!alias_node)
			return (0);
		free(info->argv[0]);
		p = _strchr(alias_node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * _replaceVars - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replaceVars(info_t *info)
{
	int i = 0;
	list_t *env_node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			_replaceString(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			_replaceString(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		env_node = _nodeStartsWith(info->envp, &(info->argv[i][1]), '=');
		if (env_node)
		{
			_replaceString(&(info->argv[i]),
				_strdup(_strchr(env_node->str, '=') + 1));
			continue;
		}
		_replaceString(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * _replaceString - replaces a string
 * @old_str: address of the old string
 * @new_str: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replaceString(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}

