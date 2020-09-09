/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_chars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 14:51:53 by nforay            #+#    #+#             */
/*   Updated: 2020/09/09 14:53:28 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prcs_redirection(t_token **token, size_t *i, t_list **iter)
{
	char	*tmp;
	size_t	len;

	while (!(len = rediroperator_length(g_shell.input + *i)))
	{
		ft_straddchar(&((*token)->text), g_shell.input[*i], 1);
		(*i)++;
	}
	tmp = (*token)->text;
	(*token)->text = ft_strnjoin((*token)->text, g_shell.input + *i, len);
	(*token)->is_operator = 1;
	ft_free(&tmp);
	*i += len;
	while (is_blank(g_shell.input[*i]))
		(*i)++;
	if (g_shell.input[*i])
		new_word(iter, token);
}

void	prcs_quote(t_token *token, size_t *i)
{
	char	*tmp;

	ft_straddchar(&(token->text), g_shell.input[*i], 1);
	tmp = token->text;
	token->text = ft_strjoinuntil(token->text, g_shell.input + *i + 1,
		g_shell.input[*i]);
	ft_free(&tmp);
	(*i) += ft_strlenuntil(g_shell.input + *i + 1, g_shell.input[*i]) + 2;
	ft_straddchar(&(token->text), g_shell.input[*i - 1], 1);
}

void	prcs_space(t_token **token, size_t *i, t_list **iter)
{
	if (g_shell.input[*i + 1])
		new_word(iter, token);
	while (is_blank(g_shell.input[*i]))
		(*i)++;
}

void	prcs_operator(t_token **token, size_t *i, t_list **iter)
{
	size_t	op_len;
	char	*tmp;

	op_len = operator_length(g_shell.input + *i);
	if (ft_strlen((*token)->text))
		new_word(iter, token);
	tmp = (*token)->text;
	(*token)->text = ft_strnjoin((*token)->text, g_shell.input + *i, op_len);
	(*token)->is_operator = 1;
	ft_free(&tmp);
	(*i) += op_len;
	while (is_blank(g_shell.input[*i]))
		(*i)++;
	if (g_shell.input[*i + 1])
		new_word(iter, token);
}

void	prcs_character(t_token *token, size_t *i)
{
	ft_straddchar(&(token->text), g_shell.input[*i], 1);
	(*i)++;
}
