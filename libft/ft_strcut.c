/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:58:25 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/23 15:31:31 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut(char *src, size_t cut_start, size_t len)
{
	char	*res;

	if (cut_start >= ft_strlen(src))
		return (src);
	if (!(res = malloc_zero(sizeof(char) * (ft_strlen(src) - len + 1))))
		return (NULL);
	ft_strncpy(res, src, cut_start);
	src += cut_start + len;
	ft_strncpy(res, src, ft_strlen(src));
	return (res);
}