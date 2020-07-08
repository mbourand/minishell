#include "libft.h"

size_t	ft_strlenuntil(char const *str, char c)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}