/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 12:55:33 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/18 12:39:53 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_command_child(size_t *i, int pipe_index)
{
	g_shell.path = parse_path(get_env(g_shell.env, "PATH"));
	pipe_redirection(get_near_pipes(g_shell.commands, *i), pipe_index);
	g_shell.lst_redir = perform_redirection(g_shell.commands + *i);
	execute_pipeline_cmd(g_shell.commands[*i], g_shell.path, &(g_shell.exit_code));
	exit(EXIT_FAILURE);
}

void	close_pipes(pid_t pids[], size_t size)
{
	size_t	i;
	size_t	pid_ind;
	pid_t	pid;
	int		status;

	i = 0;
	while (i < size)
	{
		pid_ind = 0;
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
		}
		else
		{
			close(g_shell.pipeline[pid_ind - 1][0]);
			close(g_shell.pipeline[pid_ind][1]);
		}
		i++;
	}
}

int		**alloc_pipes(size_t i)
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

void	fill_pipeline(size_t i)
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

void	free_pipeline(pid_t *pids)
{
	size_t	i;

	i = 0;
	free(pids);
	while (g_shell.pipeline[i])
		free(g_shell.pipeline[i++]);
	free(g_shell.pipeline);
}

/*
**	Fork et lance la commande dans l'enfant
**	passe à la commande d'après dans le parent
**	retourne 1 si c'était la dernière commande
*/
int		fork_and_run(size_t *i, size_t *pipe_index, pid_t *pids)
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

void	process_pipeline(size_t *i)
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
	close_pipes(pids, size + 1);
	free_pipeline(pids);
	(*i)++;
}
