#include "shell.h"

/**
 * _clearInfoStruct - Function nitializes info_t struct
 * @info: Pointer to the info_t struct
 */
void _clearInfoStruct(info_t *info)
{
	info->_args = NULL;
	info->_argv = NULL;
	info->_path = NULL;
	info->_argc = 0;
}

/**
 * _setInfoStruct - Function initializes info_t struct
 * @info: Pointer to the info_t struct
 * @argument_vector: Argument vector
 */
void _setInfoStruct(info_t *info, char **argument_vector)
{
	int i = 0;

	info->filename = argument_vector[0];
	if (info->_args)
	{
		info->_argv = strtow(info->_args, " \t");
		if (!info->_argv)
		{

			info->argument_vector = malloc(sizeof(char *) * 2);
			if (info->argument_vector)
			{
				info->_argv[0] = _strdup(info->args);
				info->_argv[1] = NULL;
			}
		}
		for (i = 0; info->_argv && info->_argv[i]; i++)
			;
		info->_argc = i;

		_replaceAlias(info);
		_replaceVariables(info);
	}
}

/**
 * _freeInfoStruct - Function frees info_t struct fields
 * @info: Pointer to the info_t struct
 * @free_all: True if freeing all fields
 */
void _freeInfoStruct(info_t *info, int free_all)
{
	_ffree(info->_argv);
	info->_argv = NULL;
	info->_path = NULL;
	if (free_all)
	{
		if (!info->_cmdBuf)
			free(info->args);
		if (info->envp)
			_freeList(&(info->envp));
		if (info->history)
			_freeList(&(info->_history));
		if (info->_alias)
			_freeList(&(info->_alias));
		_ffree(info->environ);
		info->environ = NULL;
		_bfree((void **)info->_cmdBuf);
		if (info->_readFileDescriptor > 2)
			close(info->_readFileDescriptor);
		_putchar(BUF_FLUSH);
	}
}
