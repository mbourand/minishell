/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 13:37:29 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/30 13:56:39 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_operators(t_list **commands)
{
	size_t	i;
	size_t	size;
	t_token	*content;
	int valid;

	i = 0;
	size = 0;
	while (commands[size])
		size++;
	while (commands[i])
	{
		content = (t_token*)(commands[i]->content);
		if (operator_length(content->text))
		{
			if (!ft_strcmp(content->text, ";"))
				valid = (i > 0 && !operator_length(((t_token*)commands[i - 1]->content)->text));
			else
				valid = (i > 0 && i < size - 1 && !operator_length(((t_token*)commands[i - 1]->content)->text) && !operator_length(((t_token*)commands[i + 1]->content)->text));
			if (!valid)
				break ;
		}
		i++;
	}
	return (valid);
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