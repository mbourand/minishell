/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 14:57:23 by nforay            #+#    #+#             */
/*   Updated: 2020/08/17 16:33:32 by nforay           ###   ########.fr       */
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
	if (g_shell.is_parent)
	{
		ft_putendl_fd("", 1);
		print_prompt();
	}
}

void		sighandler(void)
{
	ft_printf("\e[31m[DEBUG]\e[39mSigHandler loaded.\n");
	signal(SIGQUIT, &sig_quit); // ^\ ????
	signal(SIGINT, &sig_int); // ^C
}
