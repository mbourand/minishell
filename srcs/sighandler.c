/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:57:23 by nforay            #+#    #+#             */
/*   Updated: 2020/08/17 16:44:59 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_quit(int sig)
{
	(void)sig;
	if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mSigQuit\n");
}

static void	sig_int(int sig)
{
	(void)sig;
	if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mSigInt\n");
	ft_putendl_fd("", 1);
	if (!g_shell.input)
	{
		print_prompt();
	}
	else
		g_shell.interrupted = 1;
}

void		sighandler(void)
{
	if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mSigHandler loaded.\n");
	signal(SIGQUIT, &sig_quit); // ^\ ????
	signal(SIGINT, &sig_int); // ^C
}
