/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 13:56:34 by nforay            #+#    #+#             */
/*   Updated: 2020/09/15 14:13:02 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			export_print(t_env *env)
{
	if (env->val[0])
		ft_printf("declare -x %s=\"%s\"\n", env->key, env->val);
	else
		ft_printf("declare -x %s\n", env->key);
}

static int		check_export_key(char *key)
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

static void		export_add_or_replace(t_env *new, t_list *env)
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

static t_env	*export_parse_env(t_list *env, char *str)
{
	t_env	*new;

	if (!(new = malloc(sizeof(t_env) * 1)))
		exit(1);
	new->key = ft_strjoinuntil("", str, '=');
	if (new->key[(ft_strlen(new->key) - 1)] == '+')
	{
		str += ft_strlen(new->key) + 1;
		new->key[ft_strlen(new->key) - 1] = '\0';
		if (get_env(env, new->key))
			new->val = ft_strjoin((get_env(env, new->key))->val, str);
		else
			new->val = ft_strjoin("", str);
	}
	else
	{
		str += ft_strlen(new->key) + 1;
		new->val = ft_strjoin("", str);
	}
	return (new);
}

int				btin_export(t_list *command)
{
	t_env	*new;
	t_list	*env;

	env = g_shell.env;
	if (!((t_token*)command->next))
	{
		ft_lstiter(env, (void*)&export_print);
		return (SUCCESS);
	}
	new = export_parse_env(env, ((t_token*)command->next->content)->text);
	if (!(check_export_key(new->key)) || !new->key[0])
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: export: `%s': not a valid identifier\n",
			((t_token*)command->next->content)->text);
		free(new->key);
		free(new->val);
		free(new);
		return (FAILURE);
	}
	export_add_or_replace(new, env);
	return (SUCCESS);
}
