/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:52:59 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/12 16:34:30 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	len;
	unsigned int	tmp;
	unsigned int	i;

	tmp = (n < 0 ? -n : n);
	len = 1;
	i = 0;
	while (tmp >= 10)
	{
		len++;
		tmp /= 10;
	}
	if (!(res = (char*)malloc(sizeof(char) * (len + 1 + (n < 0)))))
		exit(1);
	tmp = (n < 0 ? -n : n);
	res[0] = '-';
	res[len + (n < 0)] = 0;
	while (i < len)
	{
		res[len - i - 1 + (n < 0)] = (tmp % 10) + '0';
		tmp /= 10;
		i++;
	}
	return (res);
}
