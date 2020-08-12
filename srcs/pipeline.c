/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 12:55:33 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/12 21:32:27 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_shell *shell, pid_t pids[], size_t size)
{
	size_t	i;
	size_t	pid_ind;
	pid_t	pid;

	i = 0;
	while (i < size)
	{
		pid_ind = 0;
		pid = waitpid(-1, NULL, 0);
		while (pids[pid_ind] != pid && pid_ind < size)
			pid_ind++;
		if (pid_ind == 0)
			close(shell->pipeline[0][1]);
		else if (pid_ind == size - 1)
			close(shell->pipeline[pid_ind - 1][0]);
		else
		{
			close(shell->pipeline[pid_ind - 1][0]);
			close(shell->pipeline[pid_ind][1]);
		}
		i++;
	}
}

int		**alloc_pipes(t_shell *shell, size_t i)
{
	t_token	*content;
	size_t	size;
	int		**res;
	size_t	j;

	j = 0;
	size = 0;
	while (shell->commands[i])
	{
		content = ((t_token*)shell->commands[i]->content);
		if (content->is_operator && !ft_strcmp(content->text, OP_PIPE))
			size++;
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

void	fill_pipeline(t_shell *shell, size_t i)
{
	t_token	*content;
	size_t	pipe_index;

	i++;
	pipe_index = 0;
	shell->pipeline = alloc_pipes(shell, i);
	while (shell->commands[i])
	{
		content = ((t_token*)shell->commands[i]->content);
		if (content->is_operator && !ft_strcmp(content->text, OP_PIPE))
		{
			if (pipe(shell->pipeline[pipe_index]) == -1)
				ft_perror("Pipe error");
			pipe_index++;
		}
		else
			break ;
		i += 2;
	}
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

void	process_pipeline(t_shell *shell, size_t *i)
{
	size_t	pipe_index;
	pid_t	*pids;
	pid_t	tmp;
	size_t	j;
	size_t	size;

	j = 0;
	pipe_index = 0;
	fill_pipeline(shell, *i);
	size = 0;
	while (shell->pipeline[size])
		size++;
	if (!(pids = malloc_zero(sizeof(pid_t) * (size + 2))))
		exit(1);
	while (shell->commands[*i])
	{
		perform_expansion(shell->commands + *i, shell->env);
		tmp = fork();
		if (tmp == 0)
		{
			shell->path = parse_path(get_env(shell->env, "PATH"));
			pipe_redirection(shell, get_near_pipes(shell->commands, *i), pipe_index);
			shell->lst_redir = perform_redirection(shell->commands + *i);
			execute_pipeline_cmd(shell->commands[*i], shell->env, shell->path, &(shell->exit_code));
			exit(EXIT_FAILURE);
			return ;
		}
		else if (is_pipe(shell->commands[*i + 1]))
		{
			pids[j] = tmp;
			*i += 2;
			pipe_index++;
			j++;
		}
		else
		{
			pids[j] = tmp;
			break ;
		}
	}
	close_pipes(shell, pids, size + 1);
	(*i)++;
	free(pids);
	j = 0;
	while (shell->pipeline[j])
	{
		ft_memdel((void**)(shell->pipeline + j));
		j++;
	}
	ft_memdel((void**)shell->pipeline);
}
