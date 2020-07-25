/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 15:03:41 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/25 20:02:55 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Retire toutes les "unquoted quotes" qui ne sont pas dans une range de protected
*/
static void		remove_quotes(t_token *token, t_list *protected)
{
	t_range	*range;
	char	*res;
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
				ft_straddchar(&res, token->text[i++], 1);
			i--;
			protected = protected->next;
			range = protected ? (t_range*)protected->content : NULL;
		}
		else if (in_quote || !is_quote(token->text[i]))
		{
			if (is_quote(token->text[i]))
				in_quote = !in_quote;
			else
				ft_straddchar(&res, token->text[i], 1);
		}
		i++;
	}
	if (!(token->text = (res ? res : malloc_zero(sizeof(char) * 1))))
		exit(1);
}

/*
**	Remplace le nom d'une variable d'environnement par sa valeur
**	et met dans protected les caractères parmi lesquels les quotes
**	ne seront pas retirés par remove_quotes
*/
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
		ft_free(&tmp);
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
	ft_free(&(token->text));
	token->text = res;
	return (env ? ft_strlen(env->val) : 0);
}

/*
**	Protected contient des t_range
**	Le maximum d'un t_range est toujours inférieur au minimum du t_range suivant dans protected
**	Les quotes dans une range de protected ne seront pas retirés par remove_quotes
*/
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

/*
**	Remplace les variable d'environnement des tokens de cmd par leur valeur
**	Retire des tokens de cmd toutes les unquoted quotes ne venant pas de l'expansion
**	d'une variable d'environnement
*/
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