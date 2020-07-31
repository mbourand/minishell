/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 02:46:37 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/31 17:09:56 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!(res = malloc_zero(sizeof(char) * (n + 1))))
		return (NULL);
	while (src[i] && i < n)
	{
		res[i] = src[i];
		i++;
	}
	return (res);
}
