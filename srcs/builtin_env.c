/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 23:50:00 by nforay            #+#    #+#             */
/*   Updated: 2020/08/16 16:22:16 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_print(t_env *env)
{
	ft_printf("%s=%s\n", env->key, env->val);
}

int			btin_env(t_list *command)
{
	if ((t_token*)command->next)
		ft_dprintf(STDERR_FILENO, "env: ‘%s’: No such file or directory\n",
		((t_token*)command->next->content)->text);
	else
		ft_lstiter(g_shell.env, (void*)&env_print);
	return (SUCCESS);
}
