/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 23:50:00 by nforay            #+#    #+#             */
/*   Updated: 2020/08/16 04:01:19 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_print(t_env *env)
{
	ft_printf("%s=%s\n", env->key, env->val);
}

int			btin_env(t_list *command)
{
	t_list	*env;

	env = g_shell.env;
	(void)command;
	ft_lstiter(env, (void*)&env_print);
	return (SUCCESS);
}
