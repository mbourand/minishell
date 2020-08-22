/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 13:56:34 by nforay            #+#    #+#             */
/*   Updated: 2020/08/17 17:03:19 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_print(t_env *env)
{
	ft_printf("declare -x %s=\"%s\"\n", env->key, env->val);
}

static int	check_export_key(char *key)
{
	if (ft_isdigit(*key))
		return (0);
	while (*key)
	{
		if (ft_isalnum(*key) || *key == '_')
			key++;
		else
			return (0);
	}
	return (1);
}

static int	export_error(t_env *new)
{
	ft_printf("minishell: export: `%s=%s': not a valid identifier\n", new->key, new->val);
	free(new->key);
	free(new->val);
	free(new);
	return (FAILURE);
}

static void	export_add_or_replace(t_env *new, t_list *env)
{
	t_env	*tmp;

	if ((tmp = get_env(env, new->key)) != NULL)
	{
		free(tmp->val);
		tmp->val = new->val;
		free(new->key);
		free(new);
	}
	else
		ft_lstadd_back(&env, ft_lstnew(new));
}

int	btin_export(t_list *command)
{
	t_env	*new;
	t_list	*env;

	env = g_shell.env;
	if (!((t_token*)command->next))
	{
		ft_lstiter(env, (void*)&export_print);
		return (SUCCESS);
	}
	new = parse_env(((t_token*)command->next->content)->text);
	if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mkey:%s|value:%s\n", new->key, new->val);
	if (!(check_export_key(new->key)))
		return (export_error(new));
	export_add_or_replace(new, env);
	return (SUCCESS);
}
