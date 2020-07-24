/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:44:13 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/23 13:28:29 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelat(t_list **lst, size_t at, void (*del)(void*))
{
	t_list *lstat; 
	t_list *tmp;

	if (!lst || !(*lst) || !del)
		return ;
	tmp = *lst;
	if (at == 0)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
		return ;
	}
	if (at == (size_t)(ft_lstsize(*lst) - 1))
	{
		tmp = ft_lstlast(*lst);
		ft_lstat(*lst, at - 1)->next = NULL;
		ft_lstdelone(tmp, del);
		return ;
	}
	lstat = ft_lstat(*lst, at);
	tmp = ft_lstat(*lst, at - 1);
	tmp->next = lstat->next;
	ft_lstdelone(lstat, del);
}