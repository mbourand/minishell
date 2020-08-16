/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:32:12 by nforay            #+#    #+#             */
/*   Updated: 2020/08/16 15:43:52 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	btin_pwd(t_list *command)
{
	char	buf[PATH_MAX];

	(void)command;
	if (!(g_shell.cwd = getcwd(buf, PATH_MAX)))
		ft_putendl_fd((get_env(g_shell.env, "PWD"))->val, STDOUT_FILENO);
	else
		ft_putendl_fd(g_shell.cwd, STDOUT_FILENO);
	return (SUCCESS);
}
