/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 02:48:06 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/04 16:12:17 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*gen_formated_path(void)
{
	char	*path;
	char	*home;
	size_t	homelen;
	char	buf[PATH_MAX];

	if (!(get_env(g_shell.env, "PWD")))
		if (!getcwd(buf, PATH_MAX))
			path = ft_strdup(".");
		else
			path = ft_strdup(getcwd(buf, PATH_MAX));
	else
		path = ft_strdup((get_env(g_shell.env, "PWD"))->val);
	if ((get_env(g_shell.env, "HOME")) != NULL)
	{
		home = (get_env(g_shell.env, "HOME"))->val;
		homelen = ft_strlen(home);
		if (homelen > 1 && ft_strnstr(path, home, homelen))
		{
			path[0] = '~';
			ft_memmove((path + 1), (path + homelen),
				ft_strlen(path) - homelen + 1);
		}
	}
	return (path);
}

void		print_prompt(void)
{
	char	*path;
	char	*user;

	path = gen_formated_path();
	if (get_env(g_shell.env, "LOGNAME"))
		user = ft_strdup((get_env(g_shell.env, "LOGNAME"))->val);
	else
		user = ft_strdup("User42");
	ft_dprintf(STDERR_FILENO, "\e[1m\e[32m%s@%s\e[39m:\e[34m%s\e[0m$ ",
	user, "minishell", path);
	free(path);
	free(user);
}
