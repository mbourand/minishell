/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 02:47:54 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/15 22:30:00 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell g_shell;

int	init_shell(char **env)
{
	g_shell.cwd = NULL;
	g_shell.commands = NULL;
	g_shell.input = NULL;
	g_shell.tokens = NULL;
	g_shell.env = NULL;
	g_shell.lst_redir = NULL;
	g_shell.path = NULL;
	g_shell.is_parent = 1;
	g_shell.interrupted = 0;
	if (!(set_cwd(&(g_shell.cwd))))
		return (0);
	if (!(g_shell.env = init_env(env)))
		return (0);
	set_shell_level();
	return (1);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	if (!init_shell(env))
		return (1);
	sighandler();
	while (1)
	{
		print_prompt();
		process_command();
	}
	return (0);
}
