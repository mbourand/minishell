/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 15:03:41 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/19 15:06:48 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*perform_expansion(char *str)
{
	size_t	i;

	i = ft_strlenuntil(str, '$');
	if (!(str[i]))
		return ;
}