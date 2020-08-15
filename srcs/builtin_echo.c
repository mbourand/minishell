/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 21:04:22 by nforay            #+#    #+#             */
/*   Updated: 2020/08/16 00:29:42 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	btin_echo(t_shell *shell, t_list *command)
{
	t_list	*tmp;

	(void)shell;
	if (!((t_token*)command->next))
		ft_putendl_fd("", 1);
	else if (!(strncmp(((t_token*)command->next->content)->text, "-n", 3)))
	{
		tmp = command->next->next;
		while (tmp)
		{
			ft_putstr_fd(((t_token*)tmp->content)->text, 1);
			if ((tmp = tmp->next) != 0)
				ft_putchar_fd(' ', 1);
		}
	}
	else
	{
		tmp = command->next;
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
