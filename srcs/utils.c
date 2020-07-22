/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:32:41 by nforay            #+#    #+#             */
/*   Updated: 2020/07/21 20:27:14 by mbourand         ###   ########.fr       */
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

void	free_token(void *ptr)
{
	t_token *token;
	if (!ptr)
		return ;

	token = (t_token*)ptr;
	ft_free(token->text);
	ft_free(ptr);
}