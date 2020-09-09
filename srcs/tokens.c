/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:38:02 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/09 14:53:13 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *text)
{
	t_token	*token;

	if (!(token = malloc(sizeof(t_token) * 1)))
		exit(1);
	token->text = text;
	token->is_operator = 0;
	return (token);
}

void	new_word(t_list **iter, t_token **token)
{
	ft_lstadd_back(iter, ft_lstnew(create_token(ft_strnew(""))));
	(*iter) = (*iter)->next;
	(*token) = (t_token*)(*iter)->content;
}

void	get_tokens(void)
{
	t_list	*begin;
	t_list	*iter;
	t_token	*token;
	size_t	i;

	begin = ft_lstnew(create_token(ft_strnew("")));
	iter = begin;
	token = (t_token*)iter->content;
	i = 0;
	while (is_blank(g_shell.input[i]))
		i++;
	while (g_shell.input[i])
	{
		if (is_quote(g_shell.input[i]))
			prcs_quote(token, &i);
		else if (is_blank(g_shell.input[i]))
			prcs_space(&token, &i, &iter);
		else if (!token->text[0] && is_redirection(g_shell.input + i) == 2)
			prcs_redirection(&token, &i, &iter);
		else if (operator_length(g_shell.input + i) > 0)
			prcs_operator(&token, &i, &iter);
		else
			prcs_character(token, &i);
	}
	g_shell.tokens = begin;
}
