/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:38:02 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/07 18:38:02 by mbourand         ###   ########.fr       */
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
	t_token* token;

	if (!(token = malloc(sizeof(t_token) * 1)))
		exit(1);
	token->text = text;
	return (token);
}

/*
**	Crée un nouveau mot en créant un nouveau token
*/
void	new_word(t_list **iter, t_token** token)
{
	ft_lstadd_back(iter, ft_lstnew(create_token(ft_strnew(""))));
	(*iter) = (*iter)->next;
	(*token) = (t_token*)(*iter)->content;
}

/*
**	Copie de shell->input dans token->text tout ce qui est entre quote
*/
static void	process_quote(t_token *token, t_shell *shell, size_t *i)
{
	ft_straddchar(&(token->text), shell->input[*i], 1);
	token->text = ft_strjoinuntil(token->text, shell->input + *i + 1, shell->input[*i]);
	(*i) += ft_strlenuntil(shell->input + *i + 1, shell->input[*i]) + 2;
	ft_straddchar(&(token->text), shell->input[*i - 1], 1);
}

/*
**	Crée un nouveau mot si il y a d'autres mots après les espaces
*/
static void process_space(t_token **token, t_shell *shell, size_t *i, t_list **iter)
{
	if (shell->input[*i + 1])
		new_word(iter, token);
	while (is_blank(shell->input[*i]))
		(*i)++;
}

/*
**	Crée un nouveau mot si il y a déjà quelque chose dans le mot
**	Copie l'opérateur dans le nouveau mot
**	Crée un nouveau mot si il y a d'autres mots après
*/
static void process_operator(t_token **token, t_shell *shell, size_t *i, t_list **iter)
{
	size_t	op_len;

	op_len = operator_length(shell->input + *i);
	if (ft_strlen((*token)->text))
		new_word(iter, token);
	(*token)->text = ft_strnjoin((*token)->text, shell->input + *i, op_len);
	(*i) += op_len;
	while (is_blank(shell->input[*i]))
		(*i)++;
	if (shell->input[*i + 1])
		new_word(iter, token);
}

/*
**	Copie le caractère dans token->text
*/
static void process_character(t_token *token, t_shell *shell, size_t *i)
{
	token->text = ft_strnjoin(token->text, shell->input + *i, 1);
	(*i)++;
}

/*
**	Découpe l'input complet shell->input en mots et les place dans shell->tokens
*/
void	get_tokens(t_shell *shell)
{
	t_list	*begin;
	t_list	*iter;
	t_token	*token;
	size_t	i;

	begin = ft_lstnew(create_token(ft_strnew("")));
	iter = begin;
	token = (t_token*)iter->content;
	i = 0;
	while (is_blank(shell->input[i]))
		i++;
	while (shell->input[i])
	{
		if (is_quote(shell->input[i]))
			process_quote(token, shell, &i);
		else if (is_blank(shell->input[i]))
			process_space(&token, shell, &i, &iter);
		else if (operator_length(shell->input + i) > 0)
			process_operator(&token, shell, &i, &iter);
		else
			process_character(token, shell, &i);
	}
	shell->tokens = begin;
}