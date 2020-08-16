/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:32:12 by nforay            #+#    #+#             */
/*   Updated: 2020/08/16 04:02:25 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	btin_pwd(t_list *command)
{
	(void)command;
	if (!(getcwd(g_shell.cwd, PATH_MAX)))
	{
		ft_perror("pwd");
		ft_putendl_fd("No such file or directory", STDOUT_FILENO);
	}
	else
		ft_putendl_fd(g_shell.cwd, STDOUT_FILENO);
	return (SUCCESS);
}
