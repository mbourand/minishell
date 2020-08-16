/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:32:12 by nforay            #+#    #+#             */
/*   Updated: 2020/08/16 14:57:51 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	btin_pwd(t_shell *shell, t_list *command)
{
	char	buf[PATH_MAX];

	(void)command;
	if (!(shell->cwd = getcwd(buf, PATH_MAX))) // break me: mkdir -p test1/test2/test3 && cd test1/test2/test3 && rm -r ../../../test1/ && cd ..
		ft_putendl_fd((get_env(shell->env, "PWD"))->val, STDOUT_FILENO);
	else
		ft_putendl_fd(shell->cwd, STDOUT_FILENO);
	return (SUCCESS);
}
