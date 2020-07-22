/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 15:03:41 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/22 03:05:02 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_var_name(char *str)
{
	char	*name;
	char	*tmp;
	size_t	i;
	
	name = NULL;
	i = 0;
	while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
	{
		tmp = name;
		name = ft_straddchar(name, str[i], 1);
		ft_free(tmp);
		i++;
	}
	return (name);
}

static int		replace_var(t_token *token, size_t i, t_list *lstenv)
{
	char	*res;
	char	*name;
	t_env	*env;

	name = get_var_name(token->text + i + 1);
	if (!(env = get_env(lstenv, name)))
	{
	}
	if (!(res = malloc(sizeof(char) * (ft_strlen(token->text) - 1 - ft_strlen(name) + ft_strlen(env->val)))))
		exit(1);
	ft_strncpy(res, token->text, i);
	ft_strncpy(res + i, env->val, ft_strlen(env->val));
	ft_strncpy(res + i + ft_strlen(env->val), token->text + i + ft_strlen(name) + 1, ft_strlen(token->text) - ft_strlen(name) - i - 1);
	token->text = res;
	return (i + ft_strlen(env->val));
}

static void expand_token(t_token *token, t_list *env)
{
	size_t	i;

	i = 0;
	while (token->text[i])
	{
		if (token->text[i] == '\'')
			i += ft_strlenuntil(token->text + i + 1, '\'') + 1;
		if (token->text[i] == '$')
			i += replace_var(token, i, env);
		else
			i++;
	}
}

void	perform_expansion(t_list *cmd, t_list *env)
{
	t_token	*content;

	while (cmd)
	{
		content = (t_token*)cmd->content;
		expand_token(content, env);
		cmd = cmd->next;
	}
}