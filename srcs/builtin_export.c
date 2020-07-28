/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 13:56:34 by nforay            #+#    #+#             */
/*   Updated: 2020/07/28 23:11:02 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	export_print(t_env *env)
{
	ft_printf("declare -x %s=\"%s\"\n", env->key, env->val);
}

int	btin_export(t_list *env, t_list	*command)
{
	t_env	*new;
	t_env	*tmp;

	if (!((t_token*)command->next))
	{
		ft_lstiter(env, (void*)&export_print);
		return (SUCCESS);
	}
	new = parse_env(((t_token*)command->next->content)->text);
	if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mkey:%s|value:%s\n", new->key, new->val);
	if ((tmp = get_env(env, new->key)) != NULL)
	{
		free(tmp->val);
		tmp->val = new->val;
		free(new->key);
		if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mkey found, changing value.\n");
	}
	else
	{
		ft_lstadd_back(&env, ft_lstnew(new));
		if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mt_env added to env.\n");
	}
	return (SUCCESS);
}
