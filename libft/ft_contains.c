/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contains.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 01:02:13 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/06 01:04:30 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_contains(char *s1, char *s2)
{
	size_t	len;

	len = ft_strlen(s2);
	while (*s1)
	{
		if (!ft_strncmp(s1, s2, len))
			return (1);
		s1++;
	}
	return (0);
}
