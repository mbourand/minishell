/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 18:08:44 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/11 05:00:25 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_operators(t_list **commands)
{
	size_t	i;
	t_token	*content;
	t_list	*iter;
	t_list	*prev;
	int valid;

	i = 0;
	prev = NULL;
	while (commands[i])
	{
		iter = commands[i];
		while (iter)
		{
			content = (t_token*)(iter->content);
			if (is_operator(content->text))
			{
				if (!ft_strcmp(content->text, OP_SEMICOL))
					valid = (prev && !is_operator(((t_token*)prev->content)->text));
				else if (!ft_strcmp(content->text, OP_PIPE))
					valid = (i > 0 && commands[i + 1] && !is_operator(((t_token*)commands[i - 1]->content)->text) && !is_operator(((t_token*)commands[i + 1]->content)->text));
				else
					valid = (prev && iter->next && !is_operator(((t_token*)prev->content)->text) && !is_operator(((t_token*)iter->next->content)->text));
				if (!valid)
					return (0);
			}
			prev = iter;
			iter = iter->next;
		}
		i++;
	}
	return (1);
}

/*
**	Quand on trouvera d'autres erreurs de parsing on pourra rajouter ici
*/
int		commands_valid(t_shell *shell)
{
	if (!check_operators(shell->commands))
		return (0);
	return (1);
}
