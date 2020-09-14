/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 15:03:41 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/09 15:22:15 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_exitcode(t_token *token, int i)
{
	char	*res;
	char	*tmp;

	tmp = ft_itoa(g_shell.exit_code);
	if (!(tmp) || !(res = malloc(sizeof(char) * (ft_strlen(token->text) - 2 +
			ft_strlen(tmp)))))
		exit(1);
	ft_strncpy(res, token->text, i);
	ft_strcpy(res + i, tmp);
	ft_strcpy(res + i + ft_strlen(tmp), token->text + i + 2);
	ft_free(&tmp);
	tmp = token->text;
	token->text = res;
	ft_free(&tmp);
	return (ft_numlen(g_shell.exit_code, 10));
}

void		remove_quotes(t_token *token, t_list *protected)
{
	t_range	*range;
	char	*res;
	size_t	i;
	char	in_quote;

	i = 0;
	res = NULL;
	in_quote = 0;
	while (token->text[i])
	{
		range = protected ? (t_range*)protected->content : NULL;
		if (protected && i == range->min)
			process_protected(&res, token, &protected, &i);
		else if ((!in_quote && is_quote(token->text[i])) ||
				in_quote == token->text[i])
			in_quote = (in_quote == token->text[i] ? 0 : token->text[i]);
		else
			ft_straddchar(&res, token->text[i], 1);
		i++;
	}
	ft_free(&(token->text));
	if (!(token->text = (res ? res : ft_strnew(""))))
		exit(1);
}

static int	replace_var(t_token *token, size_t i, t_list *lstenv,
			t_list **protected)
{
	char	*res;
	char	*name;
	t_env	*env;

	name = get_var_name(token->text + i + 1);
	if (!(env = get_env(lstenv, name)) || !(env->val[0]))
		res = ft_strjoinfree(ft_substr(token->text, 0, i + (!name)),
			ft_strdup(token->text + i + ft_strlen(name) + 1));
	else
	{
		if (!(res = malloc_zero(sizeof(char) * (ft_strlen(token->text) - 1 -
				ft_strlen(name) + ft_strlen(env->val)) + 1)))
			exit(1);
		ft_strncpy(res, token->text, i);
		ft_lstadd_back(protected, ft_lstnew(new_range(i,
			i + ft_strlen(env->val))));
		ft_strncpy(res + i, env->val, ft_strlen(env->val));
		ft_strncpy(res + i + ft_strlen(env->val), token->text + i +
		ft_strlen(name) + 1, ft_strlen(token->text) - ft_strlen(name) - i - 1);
	}
	ft_free(&(token->text));
	ft_free(&name);
	token->text = res;
	i = (name ? 0 : 1);
	return (env ? ft_strlen(env->val) : i);
}

static void	expand_token(t_token *token, t_list *env)
{
	size_t	i;
	t_list	*protected;
	int		in_quote;

	in_quote = 0;
	i = 0;
	protected = 0;
	while (token->text[i])
	{
		if (token->text[i] == '\"')
			in_quote = !in_quote;
		if (!in_quote && token->text[i] == '\'')
			i += ft_strlenuntil(token->text + i + 1, '\'') + 1;
		if (token->text[i] == '$' && token->text[i + 1] == '?')
			i += replace_exitcode(token, i);
		if (token->text[i] == '$' && !in_quote && is_quote(token->text[i + 1]))
			ft_memmove(token->text + i, token->text + i + 1,
				ft_strlen(token->text + i));
		else if (token->text[i] == '$')
			i += replace_var(token, i, env, &protected);
		else
			i++;
	}
	remove_quotes(token, protected);
	ft_lstclear(&protected, &free);
}

void		perform_expansion(t_list **cmd, t_list *env)
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
