/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 14:11:39 by nforay            #+#    #+#             */
/*   Updated: 2020/09/09 14:20:27 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**alloc_pipes(size_t i)
{
	t_token	*content;
	size_t	size;
	int		**res;
	size_t	j;

	j = 0;
	size = 0;
	while (g_shell.commands[i])
	{
		content = ((t_token*)g_shell.commands[i]->content);
		if (content->is_operator && !ft_strcmp(content->text, OP_PIPE))
			size++;
		else
			break ;
		i += 2;
	}
	if (!(res = malloc_zero(sizeof(int*) * (size + 1))))
		exit(1);
	while (j < size)
	{
		if (!(res[j] = malloc_zero(sizeof(int) * 2)))
			exit(1);
		j++;
	}
	return (res);
}

void		fill_pipeline(size_t i)
{
	t_token	*content;
	size_t	pipe_index;

	i++;
	pipe_index = 0;
	g_shell.pipeline = alloc_pipes(i);
	while (g_shell.commands[i])
	{
		content = ((t_token*)g_shell.commands[i]->content);
		if (content->is_operator && !ft_strcmp(content->text, OP_PIPE))
		{
			if (pipe(g_shell.pipeline[pipe_index]) == -1)
				ft_perror("Pipe error");
			pipe_index++;
		}
		else
			break ;
		i += 2;
	}
}
