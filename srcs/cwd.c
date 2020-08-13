/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 02:47:46 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/13 17:15:25 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	cwd = current working directory
**	-> man getcwd
*/
int	set_cwd(char **cwd, size_t size)
{
	char *buff;

	(void)size;
	buff = getcwd(NULL, 0);
	ft_strcpy(*cwd, buff);
	free(buff);
	return (1);
}
