/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 18:08:27 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/12 16:36:43 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(char *str)
{
	char	*res;

	if (!(res = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		exit(1);
	return (ft_strcpy(res, str));
}
