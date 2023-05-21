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

	info->_filename = argument_vector[0];
	if (info->_args)
	{
		info->_argv = _splitString(info->_args, " \t");
		if (!info->_argv)
		{

			info->_argv = malloc(sizeof(char *) * 2);
			if (info->_argv)
			{
				info->_argv[0] = _strdup(info->_args);
				info->_argv[1] = NULL;
			}
		}
		for (i = 0; info->_argv && info->_argv[i]; i++)
			;
		info->_argc = i;

		_replaceAlias(info);
		_replaceVars(info);
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
		if (!info->_commandBuffer)
			free(info->_args);
		if (info->_envp)
			_freeList(&(info->_envp));
		if (info->_history)
			_freeList(&(info->_history));
		if (info->_alias)
			_freeList(&(info->_alias));
		_ffree(info->_modifiedEnvp);
		info->_modifiedEnvp = NULL;
		_bfree((void **)info->_commandBuffer);
		if (info->_readFileDescriptor > 2)
			close(info->_readFileDescriptor);
		_putchar(BUF_FLUSH);
	}
}
