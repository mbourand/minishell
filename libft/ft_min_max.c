#include "libft.h"

int		ft_min(int a, int b)
{
	return (a < b ? a : b);
}

int		ft_max(int a, int b)
{
	return (a > b ? a : b);
}

size_t	min_index(int *tab, size_t size)
{
	size_t	i;
	size_t	min_ind;

	i = 1;
	min_ind = 0;
	while (i < size)
	{
		if (tab[i] < tab[min_ind])
			min_ind = i;
		i++;
	}
	return (min_ind);
}

size_t	max_index(int *tab, size_t size)
{
	size_t	i;
	size_t	max_ind;

	i = 1;
	max_ind = 0;
	while (i < size)
	{
		if (tab[i] > tab[max_ind])
			max_ind = i;
		i++;
	}
	return (max_ind);
}