/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 02:47:46 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/26 02:47:46 by mbourand         ###   ########.fr       */
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

	buff = 0;
	while (!*cwd)
	{
		if (!(*cwd = getcwd(buff, size)))
			size++;
	}
	return (1);
}