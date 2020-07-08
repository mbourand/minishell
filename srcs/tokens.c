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
 * ATTENTION : ça ne parse pas les variables
*/

t_token	*create_token(char *text, int expansion)
{
	t_token* token;

	if (!(token = malloc(sizeof(t_token) * 1)))
		exit(1);
	token->text = text;
	token->expansion = expansion;
	return (token);
}

void	get_tokens(t_shell *shell)
{
	t_list	*begin;
	t_list	*iter;
	t_token	*token;
	size_t	i;

	begin = ft_lstnew(create_token("", 1));
	iter = begin;
	token = (t_token*) iter->content;
	i = 0;
	while (shell->input[i])
	{
		if (shell->input[i] == '\'' || shell->input[i] == '\"')
		{
			token->text = ft_strjoinuntil(token->text, shell->input + i + 1, shell->input[i]);
			token->expansion = (shell->input[i] == '\"');
			i += ft_strlenuntil(shell->input + i + 1, shell->input[i]) + 2;
		}
		else if (shell->input[i] == ' ')
		{
			if (shell->input[i + 1])
			{
				ft_lstadd_back(&iter, ft_lstnew(create_token("", 1)));
				iter = iter->next;
				token = (t_token*)iter->content;
			}
			while (shell->input[i] == ' ')
				i++;
		}
		else
		{
			token->text = ft_strnjoin(token->text, shell->input + i, 1);
			i++;
		}
	}
	shell->tokens = begin;
	while (begin)
	{
		ft_printf("%s\n", ((t_token*)(begin->content))->text);
		begin = begin->next;
	}
}