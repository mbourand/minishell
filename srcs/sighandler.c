/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:57:23 by nforay            #+#    #+#             */
/*   Updated: 2020/09/12 18:01:57 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_quit(int sig)
{
	(void)sig;
	signal(SIGQUIT, SIG_IGN);
	if (!g_shell.input)
		ft_putstr_fd("\b\b  \b\b", 2);
	else
		ft_putendl_fd("Quit", 1);
	signal(SIGQUIT, &sig_quit);
}

static void	sig_int(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_IGN);
	ft_putendl_fd("", 1);
	if (!g_shell.input)
		print_prompt();
	else
		g_shell.interrupted = 1;
	g_shell.exit_code = 130;
	signal(SIGINT, &sig_int);
}

void		sighandler(void)
{
	signal(SIGQUIT, &sig_quit);
	signal(SIGINT, &sig_int);
}
