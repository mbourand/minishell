/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinuntil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:09:24 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/31 17:09:24 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinuntil(char const *s1, char const *s2, char c)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = 0;
	s2_len = 0;
	while (s1[s1_len])
		s1_len++;
	while (s2[s2_len] && s2[s2_len] != c)
		s2_len++;
	if (!(res = malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	ft_strlcpy(res, s1, s1_len + s2_len + 1);
	ft_strlcpy(res + s1_len, s2, s2_len + 1);
	return (res);
}
