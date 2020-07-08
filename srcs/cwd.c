#include "minishell.h"

/**
 *	cwd = current working directory
 *  -> man getcwd
 */
int	set_cwd(char **cwd, size_t size)
{
	char *buff;

	buff = 0;
	while (!*cwd)
	{
		if (!(*cwd = getcwd(buff, size)))
			size++;
	}
	return (1);
}