#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/*_atoi.c*/
int _isInteractive(info_t *info);
int _isdelimeter(char c, char *delimeter);
int _isAlpha(int c);
int _atoi(char *s);

/*_exit.c*/
char *_strncpy(char *destination, char *source, int max_len);
char *_strncat(char *destination, char *source, int max_len);
char *_strchr(char *str, char character);

/*_error1.c*/
int _eputchar(char c);
void _eputs(char *str);
int _putFileDescriptor(char c, int fileDescriptor);
int _putsFileDescriptor(char *str, int fileDescriptor);

/*_error2.c*/
int _erratoi(char *str);
int _printDecimal(int input, int fd);
void _printError(info_t *info, char *error_type);
void _removeComments(char *buf);

/*_builtin1.c*/
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);

/*_builtin2.c*/
int _myHistory(info_t *info);
int _unsetAlias(info_t *info, char *alias_str);
int _setAlias(info_t *info, char *alias_str);
int _printAlias(list_t *alias_node);
int _myAlias(info_t *info);

/*_environ.c*/
int _myEnv(info_t *info);
char *_getEnv(info_t *info, const char *name);
int _mySetEnv(info_t *info);
int _myUnsetEnv(info_t *info);
int _populateEnvList(info_t *info);
extern char **environ;

/*_getenv.c*/
char **_getEnvironmentStrings(info_t *info);
int _unsetEnvironmentVariable(info_t *info, char *variable);
int _setEnvironmentVariable(info_t *info, char *variable, char *value);

/*_getinfo.c*/
void _clearInfoStruct(info_t *info);
void _setInfoStruct(info_t *info, char **argument_vector);
void _freeInfoStruct(info_t *info, int free_all);


/*_getline.c*/
ssize_t _inputBuf(info_t *info, char **buffer, size_t *buffer_len);
ssize_t _getInput(info_t *info);
ssize_t _readBuffer(info_t *info, char *buffer, size_t *buffer_size);
int _getLine(info_t *info, char **buffer_ptr, size_t *buffer_length);
void _siginthandler(__attribute__((unused))int sig_num);

/*_history.c*/
char *_getHistoryFile(info_t *info);
int _writeHistory(info_t *info);
int _renumberHistory(info_t *info);
int _readHistory(info_t *info);
int _addHistoryEntry(info_t *info, char *buffer, int line_count);
int _renumberHistory(info_t *info);

/*read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/*Command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/*Convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0


/**
 * struct program_info - contains information related to a program execution
 * @_args: String generated from getline containing program arguments
 * @_argv: Array of strings generated from arguments
 * @_path: A string representing the path of the current command
 * @_argc: Count of arguments
 * @_lineCount: Line count of the program execution
 * @_errorNumber: Error code for exit functions
 * @_countLine: Flag indicating whether to count this line of input
 * @_filename: Name of the program file
 * @_envp: linked list representing the local copy of the environment variables
 * @_modifiedEnvp: Custom modified copy of the environment variables from the linked list
 * @_history: History linked list node
 * @_alias: Alias linked list node
 * @_changedEnvp: Flag indicating if the environment was changed
 * @_status: Return status of the last executed command
 * @_commandBuffer: Address of the pointer to the command buffer used for chaining commands
 * @_commandBufferType: Type of command buffer (CMD_type: ||, &&, ;)
 * @_readFileDescriptor: File descriptor used for reading line input
 * @_historyCount: Count of history line numbers
 */
typedef struct program_info
{
	char *_args;
	char **_argv;
	char *_path;
	int _argct;
	unsigned int _lineCount;
	int _errorNumber;
	int _countLine;
	char *_filename;
	list_t *_envp;
	list_t *_history;
	list_t *_alias;
	char **_modifiedEnvp;
	int _changedEnvp;
	int _status;
	char **_commandBuffer;
	int _commandBufferType;
	int _readFileDescriptor;
	int _historyCount;
} info_t;

#endif
