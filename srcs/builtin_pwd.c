/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:32:12 by nforay            #+#    #+#             */
/*   Updated: 2020/08/16 15:29:29 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	btin_pwd(t_list *command)
{
	char	buf[PATH_MAX];

	(void)command;
	if (!(g_shell.cwd = getcwd(buf, PATH_MAX))) // break me: mkdir -p test1/test2/test3 && cd test1/test2/test3 && rm -r ../../../test1/ && cd ..
		ft_putendl_fd((get_env(g_shell.env, "PWD"))->val, STDOUT_FILENO);
	else
		ft_putendl_fd(g_shell.cwd, STDOUT_FILENO);
	return (SUCCESS);
}
