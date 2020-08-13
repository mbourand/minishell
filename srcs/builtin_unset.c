/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 23:50:21 by nforay            #+#    #+#             */
/*   Updated: 2020/07/31 20:53:22 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	remove_key(t_list *env)
{
	if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mremoving key:%s val:%s\n", ((t_env*)env)->key, ((t_env*)env)->val);
	free(((t_env*)env)->key);
	free(((t_env*)env)->val);
}

int	btin_unset(t_list *env, t_list *command)
{
	t_list *tmp;
	t_list	*envtmp;
	size_t	i;

	envtmp = env;
	i = 0;
	while (envtmp)
	{
		tmp = command->next;
		while (tmp && envtmp)
		{
			if (!(ft_strcmp(((t_token*)tmp->content)->text, ((t_env*)envtmp->content)->key)))
			{
				if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mKey %s found at %d/%d.\n", ((t_token*)tmp->content)->text, i, ft_lstsize(env) - 1);
				envtmp = envtmp->next;
				tmp = command->next;
				ft_lstdelat(&env, i, (void*)&remove_key);
			}
			else
				tmp = tmp->next;
		}
		i++;
		if (envtmp && envtmp->next)
			envtmp = envtmp->next;
	}
	return (SUCCESS);
}
