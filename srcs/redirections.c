/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 13:55:20 by mbourand          #+#    #+#             */
/*   Updated: 2020/08/10 17:16:38 by mbourand         ###   ########.fr       */
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
**	Redirige le fd de filename sur le fd de to
**	-> man dup
**	-> man open
**	Mets dans lst_redir les infos de la redirection pour l'annuler après
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
	if (fd != to && (dup2(fd, to) < 0 || close(fd) < 0))
		exit(1);
}

/*
**	Choisis les fd à rediriger en fonction de l'opérateur,
**	appelle redirect() pour faire la redirection
**	puis supprime de la commande les mots servant à la redirection
**	ex. "echo coucou > test" devient "echo coucou"
*/

void	prcs_op_redir(t_list **iter, t_list **lst_redir, t_list **command, size_t *i)
{
	int to;
	int flags;
	t_token	*content;
	size_t	offset;

	offset = 0;
	content = (t_token*)(*iter)->content;
	if (rediroperator_length(content->text))
		to = !ft_strcmp(content->text, OP_REDIRIN) ? 0 : 1;
	else
	{
		to = ft_atoi(content->text);
		offset = ft_numlen(to, 10);
	}
	if (!(ft_strcmp(content->text + offset, OP_REDIRIN)))
		flags = O_RDONLY;
	else
		flags = O_WRONLY | O_CREAT | (!ft_strcmp(content->text + offset, OP_APPEND) ? O_APPEND : O_TRUNC);
	redirect(((t_token*)(*iter)->next->content)->text, to, lst_redir, flags);
	ft_lstdelat(command, *i, &free_token);
	ft_lstdelat(command, *i, &free_token);
	*iter = ft_lstat(*command, --(*i));
}

/*
**	Fais toutes les redirections d'une commande
*/

t_list	*perform_redirection(t_list **command)
{
	t_list	*lst_redir;
	t_token	*content;
	t_list	*iter;
	size_t	i;

	lst_redir = NULL;
	iter = *command;
	i = 0;
	while (iter)
	{
		content = (t_token*)iter->content;
		if (content->is_operator && rediroperator_length(content->text + (ft_isdigit(content->text[0]) ? ft_numlen(ft_atoi(content->text), 10) : 0)))
			prcs_op_redir(&iter, &lst_redir, command, &i);
		iter = iter->next;
		i++;
	}
	return (lst_redir);
}
