/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 16:41:35 by nforay            #+#    #+#             */
/*   Updated: 2020/08/16 17:37:20 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	btin_exit(t_list *command)
{
	char	*str;
	int		excode;

	ft_dprintf(STDERR_FILENO, "exit\n");
	if (!((t_token*)command->next))
		exit(0);
	else
	{
		str = ((t_token*)command->next->content)->text;
		excode = (ft_atoi(((t_token*)command->next->content)->text) % 256);
		while (excode < 0)
			excode += 256;
		while (str && (ft_isdigit(*str) || *str == 43 || *str == 45))
			str++;
		if (*str != 0)
			ft_dprintf(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n",
			((t_token*)command->next->content)->text);
		else
			exit(excode);
	}
	return (0);
}
