#include "libft.h"

char	*ft_straddchar(char *str, char c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		str = ft_strnjoin(str, &c, 1);
		i++;
	}
	return (str);
}