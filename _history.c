#include "shell.h"

/**
 * _getHistoryFile - Function gets the history file
 * @info: Parameter struct
 * Return: Allocated string containing the history file
 */

char *_getHistoryFile(info_t *info)
{
	char *buffer, *home_directory;

	home_directory = _getEnv(info, "HOME=");
	if (!home_directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(home_directory) +
		_strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, home_directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * _writeHistory - Function creates a file, or appends to an existing file
 * @info: The parameter struct
 * Return: Return 1 on success, else -1
 */
int _writeHistory(info_t *info)
{
	ssize_t file_descriptor;
	char *filename = _getHistoryFile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	file_descriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_descriptor == -1)
		return (-1);
	for (node = info->_history; node; node = node->next)
	{
		_putsFileDescriptor(node->str, file_descriptor);
		_putFileDescriptor('\n', file_descriptor);
	}
	_putFileDescriptor(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * _renumberHistory - Renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 * Return: Function return the new histcount
 */
int _renumberHistory(info_t *info)
{
	list_t *node = info->_history;
	int new_histcount = 0;

	while (node)
	{
		node->num = new_histcount++;
		node = node->next;
	}
	return (info->_historyCount = new_histcount);
}

/**
 * _buildHistoryList - Function adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: Return the history linecount, histcount
 * Return: Always 0
 */
int _buildHistoryList(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->_history)
		node = info->_history;
	_addNodeEnd(&node, buf, linecount);

	if (!info->_history)
		info->_history = node;
	return (0);
}

/**
 * _readHistory - Function reads history from file
 * @info: The parameter struct
 * Return: Return histcount on success, 0 otherwise
 */
int _readHistory(info_t *info)
{
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_stats;
	char *buffer = NULL, *filename = _getHistoryFile(info);

	if (!filename)
		return (0);

	file_descriptor = open(filename, O_RDONLY);
	free(filename);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &file_stats))
		file_size = file_stats.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			_buildHistoryList(info, buffer + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		_buildHistoryList(info, buffer + last, line_count++);
	free(buffer);
	info->_historyCount = line_count;
	while (info->_historyCount-- >= HIST_MAX)
		_deleteNodeAtIndex(&(info->_history), 0);
	_renumberHistory(info);
	return (info->_historyCount);
}

/**
 * _addHistoryEntry - Function adds an entry to the history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buffer: Buffer containing the history entry
 * @line_count: Return the line count of the history entry
 *
 * Return: Always 0
 */

int _addHistoryEntry(info_t *info, char *buffer, int line_count)
{
	list_t *new_node = NULL;

	if (info->_history)
		new_node = info->_history;
	_addNodeEnd(&new_node, buffer, line_count);

	if (!info->_history)
		info->_history = new_node;
	return (0);
}
