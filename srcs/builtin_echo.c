/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 21:04:22 by nforay            #+#    #+#             */
/*   Updated: 2020/09/04 15:33:55 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	btin_echo(t_list *command)
{
	t_list	*tmp;

	tmp = command->next;
	if (!((t_token*)tmp))
		ft_putendl_fd("", 1);
	else if (!(strncmp(((t_token*)command->next->content)->text, "-n", 3)))
	{
		while ((tmp = tmp->next))
		{
			ft_putstr_fd(((t_token*)tmp->content)->text, 1);
			if ((tmp->next) != 0)
				ft_putchar_fd(' ', 1);
		}
	}
	else
	{
		while (tmp)
		{
			ft_putstr_fd(((t_token*)tmp->content)->text, 1);
			if ((tmp = tmp->next) != 0)
				ft_putchar_fd(' ', 1);
		}
		ft_putendl_fd("", 1);
	}
	return (SUCCESS);
}
