/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 02:48:06 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/16 04:12:12 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_prompt()
{
	char	*path;
	char	*home;
	size_t	homelen;

	path = ft_strdup((get_env(g_shell.env, "PWD"))->val);
	if ((get_env(g_shell.env, "HOME")) != NULL)
	{
		home = (get_env(g_shell.env, "HOME"))->val;
		homelen = ft_strlen(home);
		if (ft_strnstr(path, home, homelen))
		{
			path[0] = '~';
			ft_memmove((path + 1), (path + homelen), ft_strlen(path) - homelen + 1);
		}
	}
	ft_printf("\e[1m\e[32m%s@%s\e[39m:\e[34m%s\e[0m$ ",
	(get_env(g_shell.env, "LOGNAME"))->val,
	"minishell",//unless I can get HOSTNAME
	path);
	free(path);
}
