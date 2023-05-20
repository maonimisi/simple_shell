#include "shell.h"
/**
 * _executeCommand - Function is the main shell loop
 * @info: The parameter & return info struct
 * @argv: The argument vector
 * Return: 0 on success, 1 on error, or error code
 */
int _executeCommand(info_t *info, char **argv)
{
	ssize_t read_result = 0;
	int builtin_ret = 0;

	while (read_result != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (_isInteractive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		read_result = _getInput(info);
		if (read_result != -1)
		{
			_setInfo(info, argv);
			builtin_ret = _findBuiltin(info);
			if (builtin_ret == -1)
				_findCommand(info);
		}
		else if (_isInteractive(info))
			_putchar('\n');
		__freeInfoStruct(info, 0);
	}
	_writeHistory(info);
	_freeInfoStruct(info, 1);
	if (!_isInteractive(info) && info->_status)
		exit(info->_status);
	if (builtin_ret == -2)
	{
		if (info->_errorNumber == -1)
			exit(info->_status);
		exit(info->_errorNumber);
	}
	return (builtin_ret);
}
