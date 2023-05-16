#include "shell.h"

/**
 * _inputBuf - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @buffer_len: address of len var
 * Return: bytes read
 */
ssize_t _inputBuf(info_t *info, char **buffer, size_t *buffer_len)
{
	ssize_t bytes_read = 0;
	size_t len_p = 0;

	if (!*buffer_len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, siginthandler);
#if USE_GETLINE
		bytes_read = getline(buffer, &len_p, stdin);
#else
		bytes_read = _getline(info, buffer, &len_p);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->_countLine = 1;
			_removeComments(*buffer);
			_buildHistoryList(info, *buffer, info->_historyCount++);
			/* if (_strchr(*buffer, ';')) is this a command chain? */
			{
				*buffer_len = bytes_read;
				info->_commandBuffer = buffer;
			}
		}
	}
	return (bytes_read);
}

/**
 * _getInput - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t _getInput(info_t *info)
{
	static char *buffer;
	static size_t buffer_start, buffer_end, buffer_len;
	ssize_t bytes_read = 0;
	char **buffer_ptr = &(info->args), *p;

	_putchar(BUF_FLUSH);
	bytes_read = _inputBuf(info, &buffer, &buffer_len);
	if (bytes_read == -1)
		return (-1);
	if (buffer_len)
	{
		buffer_end = buffer_start;
		p = buffer + buffer_start;

		_checkChain(info, buffer, &buffer_end, buffer_start, buffer_len);
		while (buffer_end < buffer_len)
		{
			if (_isChain(info, buffer, &buffer_end))
				break;
			buffer_end++;
		}

		buffer_start = buffer_end + 1;
		if (buffer_start >= buffer_len)
		{
			buffer_start = buffer_len = 0;
			info->_commandBufferType = CMD_NORM;
		}

		*buffer_ptr = p;
		return (_strlen(p));
	}

	*buffer_ptr = buffer;
	return (bytes_read);
}

#include "shell.h"

/**
 * _readBuffer - Function reads a buffer
 * @info: Parameter struct
 * @buffer: Inpur buffer
 * @buffer_size: Size of buffer
 * Return: Return bytes read
 */
ssize_t _readBuffer(info_t *info, char *buffer, size_t *buffer_size)
{
	ssize_t bytes_read = 0;

	if (*buffer_size)
		return (0);
	bytes_read = read(info->readFileDescriptor, buffer, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*buffer_size = bytes_read;
	return (bytes_read);
}

/**
 * _getLine - Function gets the next line of input from STDIN
 * @info: Parameter struct
 * @buffer_ptr: Address of pointer to buffer, preallocated or NULL
 * @buffer_length: Size of preallocated buffer if not NULL
 * Return: Return bytes read
 */
int _getLine(info_t *info, char **buffer_ptr, size_t *buffer_length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t buffer_start, buffer_end, buffer_size;
	size_t k;
	ssize_t bytes_read = 0, line_length = 0;
	char *buffer_start_ptr = NULL, *new_buffer_ptr = NULL, *c;

	buffer_start_ptr = *buffer_ptr;
	if (buffer_start_ptr && buffer_length)
		line_length = *buffer_length;
	if (buffer_start == buffer_size)
		buffer_start = buffer_size = 0;

	bytes_read = _readBuffer(info, buffer, &buffer_size);
	if (bytes_read == -1 || (bytes_read == 0 && buffer_size == 0))
		return (-1);

	c = _strchr(buffer + buffer_start, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : buffer_size;
	new_buffer_ptr = _realloc(buffer_start_ptr, line_length, line_length ?
			line_length + k : k + 1);
	if (!new_buffer_ptr) /* MALLOC FAILURE! */
		return (buffer_start_ptr ? free(buffer_start_ptr), -1 : -1);

	if (line_length)
		_strncat(new_buffer_ptr, buffer + buffer_start, k - buffer_start);
	else
		_strncpy(new_buffer_ptr, buffer + buffer_start, k - buffer_start + 1);

	line_length += k - buffer_start;
	buffer_start = k;
	buffer_start_ptr = new_buffer_ptr;

	if (buffer_length)
		*buffer_length = line_length;
	*buffer_ptr = buffer_start_ptr;
	return (line_length);
}

/**
 * _siginthandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void _siginthandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

