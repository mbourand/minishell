/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenuntil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:09:41 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/31 17:09:41 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
