/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 12:55:33 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/12 17:58:27 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_command_child(size_t *i, int pipe_index)
{
	g_shell.path = parse_path(get_env(g_shell.env, "PATH"));
	pipe_redirection(get_near_pipes(g_shell.commands, *i), pipe_index);
	g_shell.lst_redir = perform_redirection(g_shell.commands + *i);
	execute_pipeline_cmd(g_shell.commands[*i], g_shell.path);
	exit(EXIT_FAILURE);
}

static int	fork_and_run(size_t *i, size_t *pipe_index, pid_t *pids)
{
	pid_t	tmp;

	tmp = fork();
	if (tmp == 0)
	{
		g_shell.is_parent = 0;
		run_command_child(i, *pipe_index);
		return (0);
	}
	else
	{
		g_shell.is_parent = 1;
		pids[(*pipe_index)++] = tmp;
		if (is_pipe(g_shell.commands[*i + 1]))
			*i += 2;
		else
			return (1);
		return (0);
	}
}

static void	close_pipes(size_t i, pid_t pids[], size_t size, size_t pid_ind)
{
	pid_t	pid;
	int		status;

	while (i < size && !(pid_ind = 0))
	{
		pid = waitpid(-1, &status, 0);
		while (pids[pid_ind] != pid && pid_ind < size)
			pid_ind++;
		if (pid_ind == 0)
			close(g_shell.pipeline[0][1]);
		else if (pid_ind == size - 1)
		{
			close(g_shell.pipeline[pid_ind - 1][0]);
			if (WIFEXITED(status))
				g_shell.exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_shell.exit_code = 128 + status;
		}
		else if (pid_ind)
		{
			close(g_shell.pipeline[pid_ind - 1][0]);
			close(g_shell.pipeline[pid_ind][1]);
		}
		i++;
	}
}

static void	free_pipeline(pid_t *pids)
{
	size_t	i;

	i = 0;
	free(pids);
	while (g_shell.pipeline[i])
		free(g_shell.pipeline[i++]);
	free(g_shell.pipeline);
}

void		process_pipeline(size_t *i)
{
	size_t	pipe_index;
	pid_t	*pids;
	size_t	size;

	pipe_index = 0;
	size = 0;
	fill_pipeline(*i);
	while (g_shell.pipeline[size])
		size++;
	if (!(pids = malloc_zero(sizeof(pid_t) * (size + 2))))
		exit(1);
	while (g_shell.commands[*i])
	{
		perform_expansion(g_shell.commands + *i, g_shell.env);
		if (fork_and_run(i, &pipe_index, pids))
			break ;
	}
	close_pipes(0, pids, size + 1, 0);
	free_pipeline(pids);
	(*i)++;
}
