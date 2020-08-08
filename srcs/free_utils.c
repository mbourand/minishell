/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 14:53:08 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/07 18:52:34 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_nothing(void *ptr)
{
	(void)ptr;
}

void	free_token(void *ptr)
{
	t_token *token;

	if (!ptr)
		return ;
	token = (t_token*)ptr;
	ft_free(&(token->text));
	ft_memdel(&ptr);
}

void	free_shell(t_shell *shell)
{
	size_t	i;
	void	*cast;

	i = 0;
	cast = (void*)shell->commands;
	ft_free(&(shell->input));
	ft_lstclear(&(shell->tokens), &free_nothing);
	while (shell->commands[i])
		ft_lstclear(&(shell->commands[i++]), &free_token);
	ft_memdel(&cast);
	i = 0;
	cast = (void*)shell->path;
	ft_memdel(&cast);
}
