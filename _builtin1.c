#include "shell.h"
/**
 * _myExit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit"
 */
int _myExit(info_t *info)
{
	int exit_status;

	if (info->_argv[1])
	{
		exit_status = _erratoi(info->_argv[1]);
		if (exit_status == -1)
		{
			info->_status = 2;
			_printError(info, "Illegal number: ");
			_eputs(info->_argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->_errorNumber = _erratoi(info->_argv[1]);
		return (-2);
	}
	info->_errorNumber = -1;
	return (-2);
}

/**
 * _myCd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int _myCd(info_t *info)
{
	char *current_dir, *new_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->_argv[1])
		new_dir = _getEnv(info, "HOME=");
	else if (_strcmp(info->_argv[1], "-") == 0)
	{
		if (!_getEnv(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		new_dir = _getEnv(info, "OLDPWD=");
	}
	else
		new_dir = info->_argv[1];

	chdir_ret = chdir(new_dir);
	if (chdir_ret == -1)
	{
		_printError(info, "can't cd to ");
		_eputs(info->_argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setEnvironmentVariable(info, "OLDPWD", _getEnv(info, "PWD="));
		_setEnvironmentVariable(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}


/**
 * _myHelp - Function prints help information
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int _myHelp(info_t *info)
{
	char **arg_array;

	arg_array = info->_argv;
	_puts("help call works. Function not yet implemented\n");
	if (0)
		_puts(*arg_array);
	return (0);
}
