/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:32:12 by nforay            #+#    #+#             */
/*   Updated: 2020/08/16 00:59:16 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	btin_pwd(t_shell *shell, t_list *command)
{
	(void)command;
	if (!(getcwd(shell->cwd, PATH_MAX)))
	{
		ft_perror("pwd");
		ft_putendl_fd("No such file or directory", STDOUT_FILENO);
	}
	else
		ft_putendl_fd(shell->cwd, STDOUT_FILENO);
	return (SUCCESS);
}
