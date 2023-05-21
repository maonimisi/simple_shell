#include "shell.h"
/**
 * _findBuiltin - finds a builtin command
 * @info: the parameter & return info struct
 * Return: -1 if builtin not found,
 *          0 if builtin executed successfully,
 *          1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int _findBuiltin(info_t *info)
{
	int i, builtin_ret = -1;
	builtin_table builtin_tbl[] = {
		{"exit", _myExit},
		{"env", _myEnv},
		{"help", _myHelp},
		{"history", _myHistory},
		{"setenv", _mySetEnv},
		{"unsetenv", _myUnsetEnv},
		{"cd", _myCd},
		{"alias", _myAlias},
		{NULL, NULL}
	};

	for (i = 0; builtin_tbl[i].type; i++)
	{
		if (_strcmp(info->_argv[0], builtin_tbl[i].type) == 0)
		{
			info->_lineCount++;
			builtin_ret = builtin_tbl[i].func(info);
			break;
		}
	}

	return (builtin_ret);
}

/**
 * _findCommand - Function finds a command in PATH
 * @info: the parameter & return info struct
 * Return: void
 */
void _findCommand(info_t *info)
{
	char *path = NULL;
	int i, num_args;

	info->_path = info->_argv[0];

	if (info->_countLine == 1)
	{
		info->_lineCount++;
		info->_countLine = 0;
	}
	for (i = 0, num_args  = 0; info->_args[i]; i++)
		if (!_isDelimeter(info->_args[i], " \t\n"))
			num_args++;
	if (!num_args)
		return;

	path = _findCommandPath(info, _getEnv(info, "PATH="), info->_argv[0]);
	if (path)
	{
		info->_path = path;
		_forkCommand(info);
	}
	else
	{
		if ((_isInteractive(info) || _getEnv(info, "PATH=") || info->_argv[0][0]
			== '/') && _isExecutableCommand(info, info->_argv[0]))
			_forkCommand(info);
		else if (*(info->_args) != '\n')
		{
			info->_status = 127;
			_printError(info, "Not Found\n");
		}
	}
}

/**
 * _forkCommand - Function forks an exec thread to run a command
 * @info: the parameter & return info struct
 * Return: void
 */
void _forkCommand(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(info->_path, info->_argv, _getEnvironmentStrings(info)) == -1)
		{
			_freeInfoStruct(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->_status));
		if (WIFEXITED(info->_status))
		{
			info->_status = WEXITSTATUS(info->_status);
			if (info->_status == 126)
				_printError(info, "Permission denied\n");
		}
	}
}
