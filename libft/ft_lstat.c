/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 20:14:05 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/21 20:15:10 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstat(t_list *lst, size_t at)
{
	if (!lst)
		return (NULL);
	while (at > 0 && lst)
	{
		lst = lst->next;
		at--;
	}
	return (lst);
}