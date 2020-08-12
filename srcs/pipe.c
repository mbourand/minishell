/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 13:35:49 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/12 17:41:06 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_pipe(t_list *command)
{
	t_token	*content;

	if (!command)
		return (FALSE);
	content = (t_token*)command->content;
	return (content->is_operator && !ft_strcmp(content->text, OP_PIPE));
}

int		get_near_pipes(t_list **command, size_t i)
{
	int res;

	res = i > 0 ? is_pipe(command[i - 1]) : 0;
	res |= (is_pipe(command[i + 1]) << 1);
	return (res);
}
