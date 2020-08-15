/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 02:47:46 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/16 01:07:10 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	cwd = current working directory
**	-> man getcwd
*/
int	set_cwd(char **cwd)
{
	char	buf[PATH_MAX];

	*cwd = getcwd(buf, PATH_MAX);
	return (1);
}
