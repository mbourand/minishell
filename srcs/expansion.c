/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 15:03:41 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/24 15:11:42 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		remove_quotes(t_token *token, t_list *protected)
{
	t_range	*range;
	char	*res;
	char	*tmp;
	size_t	i;
	int		in_quote;
	
	i = 0;
	range = protected ? (t_range*)protected->content : NULL;
	res = NULL;
	in_quote = 0;
	while (token->text[i])
	{
		if (protected && i == range->min)
		{
			while (i < range->max)
			{
				tmp = res;
				res = ft_straddchar(res, token->text[i], 1);
				ft_free(tmp);
				i++;
			}
			i--;
			protected = protected->next;
			range = protected ? (t_range*)protected->content : NULL;
		}
		else if (in_quote || !is_quote(token->text[i]))
		{
			if (is_quote(token->text[i]))
				in_quote = !in_quote;
			else
			{
				tmp = res;
				res = ft_straddchar(res, token->text[i], 1);
				ft_free(tmp);
			}
		}
		i++;
	}
	if (!(token->text = (res ? res : malloc_zero(sizeof(char) * 1))))
		exit(1);
}

static int		replace_var(t_token *token, size_t i, t_list *lstenv, t_list **protected)
{
	char	*res;
	char	*name;
	char	*tmp;
	t_env	*env;

	name = get_var_name(token->text + i + 1);
	if (!(env = get_env(lstenv, name)) || !(env->val[0]))
	{
		res = ft_substr(token->text, 0, i);
		tmp = res;
		res = ft_strjoin(res, token->text + i + ft_strlen(name) + 1);
		ft_free(tmp);
	}
	else
	{
		if (!(res = malloc(sizeof(char) * (ft_strlen(token->text) - 1 - ft_strlen(name) + ft_strlen(env->val)))))
			exit(1);
		ft_strncpy(res, token->text, i);
		ft_lstadd_back(protected, ft_lstnew(new_range(i, i + ft_strlen(env->val))));
		ft_strncpy(res + i, env->val, ft_strlen(env->val));
		ft_strncpy(res + i + ft_strlen(env->val), token->text + i + ft_strlen(name) + 1, ft_strlen(token->text) - ft_strlen(name) - i - 1);
	}
	ft_free(token->text);
	token->text = res;
	return (env ? ft_strlen(env->val) : 0);
}

static void expand_token(t_token *token, t_list *env)
{
	size_t	i;
	t_list	*protected;

	i = 0;
	protected = 0;
	while (token->text[i])
	{
		if (token->text[i] == '\'')
			i += ft_strlenuntil(token->text + i + 1, '\'') + 1;
		if (token->text[i] == '$')
			i += replace_var(token, i, env, &protected);
		else
			i++;
	}
	remove_quotes(token, protected);
	ft_lstclear(&protected, &free);
}

void	perform_expansion(t_list **cmd, t_list *env)
{
	t_token	*content;
	int		empty;
	size_t	i;
	t_list	*iter;

	i = 0;
	iter = *cmd;
	while (iter)
	{
		content = (t_token*)iter->content;
		empty = content->text[0] == '\0';
		expand_token(content, env);
		if (!empty && !(content->text[0]))
			ft_lstdelat(cmd, i--, &free_token);
		iter = iter->next;
		i++;
	}
}