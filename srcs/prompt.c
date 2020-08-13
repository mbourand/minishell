/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 02:48:06 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/13 17:03:19 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_prompt(t_shell *shell)
{
	char	*path;
	size_t	homelen;

	path = ft_strdup((get_env(shell->env, "PWD"))->val);
	homelen = ft_strlen((get_env(shell->env, "HOME"))->val);
	if (ft_strnstr(path, (get_env(shell->env, "HOME"))->val, homelen))
	{
		path[0] = '~';
		ft_memmove((path + 1), (path + homelen), ft_strlen(path) - homelen + 1);
	}
	ft_printf("\e[1m\e[32m%s@%s\e[39m:\e[34m%s\e[0m$ ",
	(get_env(shell->env, "USER"))->val,
	(get_env(shell->env, "NAME"))->val,
	path);
	free(path);
}
