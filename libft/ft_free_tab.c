/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 21:50:37 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/06 21:56:08 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(char ***tab)
{
	size_t	i;

	if (!tab || !(*tab))
		return ;
	i = 0;
	while ((*tab)[i])
	{
		ft_free((*tab) + i);
		i++;
	}
	free(*tab);
	*tab = NULL;
}
