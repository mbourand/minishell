/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:32:41 by nforay            #+#    #+#             */
/*   Updated: 2020/07/14 18:18:34 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char *s)
{
	char	*errstr;
	char	*prefix;

	errstr = strerror(errno);
	if (!s || *s == '\0')
		prefix = "";
	else
		prefix = ": ";
	ft_putstr_fd((char *)s, 2);
	ft_putstr_fd((char *)prefix, 2);
	ft_putendl_fd((char *)errstr, 2); //ft_dprintf plus clean maybe
}
