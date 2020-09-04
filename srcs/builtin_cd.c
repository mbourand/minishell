/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 14:57:45 by nforay            #+#    #+#             */
/*   Updated: 2020/09/04 15:18:07 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_pwd(t_list *env, t_list *command)
{
	char	buf[PATH_MAX];
	char	*tmp;
	char	*ptr;

	ptr = (get_env(env, "PWD"))->val;
	if (!ft_strcpy(g_shell.cwd, getcwd(buf, PATH_MAX)))
	{
		ft_dprintf(STDERR_FILENO, "cd: error retrieving current directory: ");
		ft_dprintf(STDERR_FILENO, "getcwd: cannot access parent directories: ");
		ft_dprintf(STDERR_FILENO, "No such file or directory\n");
		tmp = ft_strjoin("/", ((t_token*)command->next->content)->text);
		(get_env(env, "PWD"))->val = ft_strjoinfree(ptr, tmp);
	}
	else
	{
		if ((get_env(env, "OLDPWD"))->val)
		{
			free((get_env(env, "OLDPWD"))->val);
			(get_env(env, "OLDPWD"))->val = (get_env(env, "PWD"))->val;
		}
		else
			free((get_env(env, "PWD"))->val);
		(get_env(env, "PWD"))->val = ft_strdup(g_shell.cwd);
	}
}

static int	changedir_home(t_list *env, t_list *command)
{
	if (get_env(env, "HOME") && !(chdir((get_env(env, "HOME"))->val)))
	{
		update_env_pwd(env, command);
		return (SUCCESS);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: ");
		if (get_env(env, "HOME"))
			ft_perror((get_env(env, "HOME"))->val);
		else
			ft_dprintf(STDERR_FILENO, "HOME not set\n");
		return (FAILURE);
	}
}

static int	changedir_path(t_list *env, t_list *command)
{
	if (!(chdir(((t_token*)command->next->content)->text)))
	{
		update_env_pwd(env, command);
		return (SUCCESS);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: ");
		ft_perror(((t_token*)command->next->content)->text);
		return (FAILURE);
	}
}

static void	fix_missing(t_list *env)
{
	t_list	*new;
	char	*tmp;
	char	buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	if (!(get_env(env, "PWD")))
	{
		tmp = ft_strjoin("PWD=", buf);
		if (!(new = ft_lstnew(parse_env(tmp))))
			exit(1);
		ft_lstadd_back(&env, new);
		free(tmp);
	}
	if (!(get_env(env, "OLDPWD")))
	{
		tmp = ft_strjoin("OLDPWD=", buf);
		if (!(new = ft_lstnew(parse_env(tmp))))
			exit(1);
		ft_lstadd_back(&env, new);
		free(tmp);
	}
}

int			btin_cd(t_list *command)
{
	fix_missing(g_shell.env);
	if (!((t_token*)command->next))
		return (changedir_home(g_shell.env, command));
	else
		return (changedir_path(g_shell.env, command));
}
