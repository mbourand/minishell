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

/** découpe l'input en mots 
 * echo world donne { "echo", "world" }
 * echo "world bonjour" test donne { "echo", "world bonjour", "test" }
 * echo world bonjour|test donne { "echo", "world", "bonjour", "|", "test" }
 * ATTENTION : ça ne parse pas les variables
*/

void	set_expansion(t_token *token, char *str, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		token->expansion = ft_strnjoin(token->expansion, str, 1);
		i++;
	}
}

/* ça revient à return 1 si il y a un operateur mais le code est extensible à n caractères pour les opérateurs */
size_t	operator_length(char *str)
{
	static char	*operators[] = { ";", "|", 0 };
	size_t		len;
	size_t		i;

	i = 0;
	while (operators[i])
	{
		len = ft_strlen(operators[i]);
		if (!(ft_strncmp(str, operators[i], len)))
			return (len);
		i++;
	}
	return (0);
}

t_token	*create_token(char *text, char *expansion)
{
	t_token* token;

	if (!(token = malloc(sizeof(t_token) * 1)))
		exit(1);
	token->text = text;
	token->expansion = expansion;
	return (token);
}

void	new_word(t_list **iter, t_token** token)
{
	ft_lstadd_back(iter, ft_lstnew(create_token("", "")));
	(*iter) = (*iter)->next;
	(*token) = (t_token*)(*iter)->content;
}

void	get_tokens(t_shell *shell)
{
	t_list	*begin;
	t_list	*iter;
	t_token	*token;
	size_t	i;
	size_t	op_len;

	begin = ft_lstnew(create_token("", ""));
	iter = begin;
	token = (t_token*)iter->content;
	i = 0;
	while (shell->input[i] == ' ')
		i++;
	while (shell->input[i])
	{
		if (shell->input[i] == '\'' || shell->input[i] == '\"')
		{
			set_expansion(token, (shell->input[i] == '\"') ? "1" : "0", ft_strlenuntil(shell->input + i + 1, shell->input[i]));
			token->text = ft_strjoinuntil(token->text, shell->input + i + 1, shell->input[i]);
			i += ft_strlenuntil(shell->input + i + 1, shell->input[i]) + 2;
		}
		else if (shell->input[i] == ' ')
		{
			if (shell->input[i + 1])
				new_word(&iter, &token);
			while (shell->input[i] == ' ')
				i++;
		}
		else if ((op_len = operator_length(shell->input + i)) > 0)
		{
			if (token->text[0])
				new_word(&iter, &token);
			token->text = ft_strnjoin(token->text, shell->input + i, op_len);
			set_expansion(token, "0", op_len);
			i += op_len;
			while (shell->input[i] == ' ')
				i++;
			if (shell->input[i + 1])
				new_word(&iter, &token);
		}
		else
		{
			token->text = ft_strnjoin(token->text, shell->input + i, 1);
			set_expansion(token, "1", 1);
			i++;
		}
	}
	shell->tokens = begin;
	while (begin)
	{
		ft_printf("%s\n%s\n", ((t_token*)(begin->content))->text, ((t_token*)(begin->content))->expansion);
		begin = begin->next;
	}
}