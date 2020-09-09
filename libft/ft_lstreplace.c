/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 19:05:50 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/09 12:30:25 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstreplace(t_list *lst, size_t at, void (*del)(void*), void *content)
{
	lst = ft_lstat(lst, at);
	del(lst->content);
	lst->content = content;
}
