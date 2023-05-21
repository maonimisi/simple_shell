#include "shell.h"
/**
 * _listLen - function that returns the number of elements in a linked list_t
 * @h: pointer to struct of type list_t
 * Return: number of elements in a linked list
 */
size_t _listLen(const list_t *h)
{
	int i = 0;

	while (h != NULL)
	{
		i++;
		h = h->next;
	}
	return (i);
}

/**
 * _listToStrings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **_listToStrings(list_t *head)
{
	list_t *node = head;
	size_t i = _listLen(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * _printList - Function prints all elements of a list_t linked list
 * @h: Pointer to first node
 * Return: Size of list
 */

size_t _printList(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(_convertNumber(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _nodeStartsWith - Function returns node whose string starts with prefix
 * @node: Pointer to list head
 * @prefix: String to match
 * @c: The next character after prefix to match
 * Return: Return node or null
 */
list_t *_nodeStartsWith(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = _startsWith(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * _getNodeIndex - Function gets the index of a node
 * @head: Pointer to list head
 * @node: Pointer to the node
 * Return: index of node or -1
 */
ssize_t _getNodeIndex(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

