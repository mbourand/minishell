#include "minishell.h"

size_t	operator_length(char *str)
{
	static char	*operators[] = { ";", "|", "<", ">>", ">", 0 };
	size_t		len;
	size_t		i;

	i = 0;
	while (operators[i])
	{
		len = ft_strlen(operators[i]);
		if (!(ft_strncmp(str, operators[i], len)))
			return (len);
		i++;
	}
	return (0);
}

size_t	ctrloperator_length(char *str)
{
	static char	*operators[] = { ";", "|", 0 };
	size_t		len;
	size_t		i;

	i = 0;
	while (operators[i])
	{
		len = ft_strlen(operators[i]);
		if (!(ft_strncmp(str, operators[i], len)))
			return (len);
		i++;
	}
	return (0);
}