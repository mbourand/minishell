/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 21:04:22 by nforay            #+#    #+#             */
/*   Updated: 2020/09/15 01:49:32 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_newline(t_list *lst)
{
	while (lst)
	{
		ft_putstr_fd(((t_token*)lst->content)->text, 1);
		if ((lst = lst->next) != 0)
			ft_putchar_fd(' ', 1);
	}
	ft_putendl_fd("", 1);
}

int			btin_echo(t_list *command)
{
	t_list	*tmp;
	int		newline;

	newline = 1;
	tmp = command->next;
	if (!((t_token*)tmp))
		ft_putendl_fd("", 1);
	while (tmp && !(strncmp(((t_token*)tmp->content)->text, "-n", 3)))
	{
		newline = 0;
		tmp = tmp->next;
	}
	if (!newline)
	{
		while (tmp)
		{
			ft_putstr_fd(((t_token*)tmp->content)->text, 1);
			if ((tmp = tmp->next) != 0)
				ft_putchar_fd(' ', 1);
		}
	}
	else
		echo_newline(tmp);
	return (SUCCESS);
}
