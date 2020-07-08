/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tobase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 08:52:49 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/06 16:14:52 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_tobase(unsigned long n, char *base)
{
	int				len;
	unsigned long	tmp;
	char			*res;
	unsigned int	base_len;

	if (!base)
		return (0);
	base_len = ft_strlen(base);
	if (base_len <= 1)
		return (0);
	len = number_lenl(n, base_len);
	if (!(res = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	tmp = n;
	res[len] = 0;
	while (len-- > 0)
	{
		res[len] = base[tmp % base_len];
		tmp /= base_len;
	}
	return (res);
}
