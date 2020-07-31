/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:08:27 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/31 17:09:58 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(char *str)
{
	char	*res;

	if (!(res = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	return (ft_strcpy(res, str));
}
