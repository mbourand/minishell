/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 13:55:20 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/03 03:19:37 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*first_with_target(int target, t_list *lst)
{
	t_redir	*redir;

	while (lst)
	{
		redir = (t_redir*)lst->content;
		if (redir->target == target)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

/*
**	Ferme le fd de from
**	ouvre le fichier destination à l'ancien fd de from
*/

void	redirect(char *filename, int to, t_list **lst_redir, int oflag)
{
	t_list	*elem;
	t_redir	*redir;
	int		fd;

	if (!(elem = first_with_target(to, *lst_redir)))
	{
		ft_lstadd_back(lst_redir, (elem = ft_lstnew(malloc_zero(sizeof(t_redir)))));
		redir = (t_redir*)elem->content;
		redir->target = to;
		redir->save = dup(to);
	}
	if (close(to) < 0)
		exit(1);
	if ((fd = open(filename, oflag, 0666)) < 0)
		exit(1);
}

/*
**	Fais toutes les redirections d'une commande
**	les sauvegarde dans lst_redir pour pouvoir les annuler après la commande
**	Supprime des arguments de la commande l'opérateur et le nom du fichier
*/

t_list	*perform_redirection(t_list **command)
{
	t_list	*lst_redir;
	t_token	*content;
	t_list	*iter;
	size_t	i;
	int		to;

	lst_redir = NULL;
	iter = *command;
	i = 0;
	while (iter)
	{
		content = (t_token*)iter->content;
		if (content->is_operator && rediroperator_length(content->text))
		{
			if (!(ft_strcmp(content->text, OP_APPEND)))
			{
			}
			else
			{
				to = !ft_strcmp(content->text, OP_REDIRIN) ? 0 : 1;
				redirect(((t_token*)iter->next->content)->text, to, &lst_redir, to == 0 ? O_RDONLY : (O_WRONLY | O_CREAT));
				ft_lstdelat(command, i, &free_token);
				ft_lstdelat(command, i, &free_token);
				iter = ft_lstat(*command, --i);
			}
		}
		iter = iter->next;
		i++;
	}
	return (lst_redir);
}
