/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:21:14 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/31 17:21:14 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
