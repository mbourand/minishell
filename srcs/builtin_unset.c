/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 23:50:21 by nforay            #+#    #+#             */
/*   Updated: 2020/09/04 15:37:03 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_key(t_list *env)
{
	free(((t_env*)env)->key);
	free(((t_env*)env)->val);
	free(env);
}

int			btin_unset(t_list *command)
{
	t_list	*tmp;
	t_list	*envtmp;
	size_t	i;

	envtmp = g_shell.env;
	i = 0;
	while (envtmp && i < (size_t)ft_lstsize(g_shell.env))
	{
		tmp = command->next;
		while (tmp && envtmp)
			if (!(ft_strcmp(((t_token*)tmp->content)->text,
				((t_env*)envtmp->content)->key)))
			{
				envtmp = envtmp->next;
				tmp = command->next;
				ft_lstdelat(&g_shell.env, i, (void*)&remove_key);
			}
			else
				tmp = tmp->next;
		i++;
		if (envtmp && envtmp->next)
			envtmp = envtmp->next;
	}
	return (SUCCESS);
}
