/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 13:35:49 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/12 23:58:41 by mbourand         ###   ########.fr       */
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

void	pipe_redirection(t_shell *shell, int pipes, int pipe_index)
{
	size_t	i;

	i = 0;
	if (pipes & PIPE_AFTER)
	{
		if (dup2(shell->pipeline[pipe_index][1], STDOUT_FILENO) == -1)
			ft_perror("Redirection error");
	}
	if (pipes & PIPE_BEFORE)
	{
		if (dup2(shell->pipeline[pipe_index - 1][0], STDIN_FILENO) == -1)
			ft_perror("Redirection error");
	}
	while (shell->pipeline[i])
	{
		close(shell->pipeline[i][0]);
		close(shell->pipeline[i][1]);
		i++;
	}
}
