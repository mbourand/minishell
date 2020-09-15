/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 16:41:35 by nforay            #+#    #+#             */
/*   Updated: 2020/09/15 14:35:15 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	whitespace(char c)
{
	return (c == ' ' || c == '\v' || c == '\f' || c == '\r' || c == '\n'
		|| c == '\t');
}

static int	bt_exit_atoi(const char *str)
{
	double				res;
	int					sign;
	int					i;

	i = 0;
	while (whitespace(str[i]))
		i++;
	sign = (str[i] == '-' ? -1 : 1);
	i += (str[i] == '-' || str[i] == '+' ? 1 : 0);
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	if ((res * sign) < LLONG_MIN || (res * sign) > LLONG_MAX)
	{
		ft_dprintf(STDERR_FILENO, MINISHELL_ERR3, str);
		return (2);
	}
	return (res * sign);
}

int			btin_exit(t_list *command)
{
	char	*str;
	int		excode;

	ft_dprintf(STDERR_FILENO, "exit\n");
	if (!((t_token*)command->next))
		exit(g_shell.exit_code);
	else if (ft_lstsize(command) == 2)
	{
		str = ((t_token*)command->next->content)->text;
		excode = (bt_exit_atoi(((t_token*)command->next->content)->text) % 256);
		while (excode < 0)
			excode += 256;
		while (str && (ft_isdigit(*str) || *str == 43 || *str == 45))
			str++;
		if (*str != 0)
		{
			ft_dprintf(STDERR_FILENO, MINISHELL_ERR3,
			((t_token*)command->next->content)->text);
			exit(2);
		}
		else
			exit(excode);
	}
	exit(1);
	return (0);
}
