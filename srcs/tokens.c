/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:38:02 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/04 16:22:03 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	découpe l'input en mots (= token dans le code)
**	echo world donne { "echo", "world" }
**	echo "world bonjour" test donne { "echo", "world bonjour", "test" }
**	echo world bonjour|test donne { "echo", "world", "bonjour", "|", "test" }
**	ATTENTION : ça ne parse pas les variables
*/
t_token	*create_token(char *text)
{
	t_token	*token;

	if (!(token = malloc(sizeof(t_token) * 1)))
		exit(1);
	token->text = text;
	token->is_operator = 0;
	return (token);
}

/*
**	Crée un nouveau mot en créant un nouveau token
*/
void	new_word(t_list **iter, t_token **token)
{
	ft_lstadd_back(iter, ft_lstnew(create_token(ft_strnew(""))));
	(*iter) = (*iter)->next;
	(*token) = (t_token*)(*iter)->content;
}

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

/*
**	Copie de shell->input dans token->text tout ce qui est entre quote
*/
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

/*
**	Crée un nouveau mot si il y a d'autres mots après les espaces
*/
void	prcs_space(t_token **token, size_t *i, t_list **iter)
{
	if (g_shell.input[*i + 1])
		new_word(iter, token);
	while (is_blank(g_shell.input[*i]))
		(*i)++;
}

/*
**	Crée un nouveau mot si il y a déjà quelque chose dans le mot
**	Copie l'opérateur dans le nouveau mot
**	Crée un nouveau mot si il y a d'autres mots après
*/
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

/*
**	Copie le caractère dans token->text
*/
void	prcs_character(t_token *token, size_t *i)
{
	ft_straddchar(&(token->text), g_shell.input[*i], 1);
	(*i)++;
}

/*
**	Découpe l'input complet shell->input en mots et les place dans shell->tokens
*/
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
		// Si il y a rien dans le token, si derrière shell->input + i + longueur de atoi c'est un opérateur de redir, c'est une redirection avec fd
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
