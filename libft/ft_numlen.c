/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 04:02:50 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/04 04:09:28 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numlen(int i, size_t base)
{
	size_t	res;
	size_t	pos;

	res = i < 0 ? 2 : 1;
	pos = i < 0 ? -i : i;
	while (pos > base - 1)
	{
		res++;
		pos /= base;
	}
	return (res);
}
