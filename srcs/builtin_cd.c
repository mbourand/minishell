/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 14:57:45 by nforay            #+#    #+#             */
/*   Updated: 2020/08/16 15:31:03 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_pwd(t_list *env, t_list *command)
{
	char	buf[PATH_MAX];
	char	*tmp;
	char	*ptr;

	ptr = (get_env(env, "PWD"))->val;
	if (!(g_shell.cwd = getcwd(buf, PATH_MAX)))
	{ // break me: mkdir -p test1/test2/test3 && cd test1/test2/test3 && rm -r ../../../test1/ && cd ..
		ft_dprintf(STDERR_FILENO, "cd: error retrieving current directory: ");
		ft_dprintf(STDERR_FILENO, "getcwd: cannot access parent directories: ");
		ft_dprintf(STDERR_FILENO, "No such file or directory\n");
		tmp = ft_strjoin("/", ((t_token*)command->next->content)->text);
		(get_env(env, "PWD"))->val = ft_strjoin(ptr, tmp);
		free(ptr);
		free(tmp);
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
	//DIR		*folder; //Maybe unnecessary to try open before chdir
	if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mchange working dir: %s\n", (get_env(env, "HOME"))->val);
	/*if (!(folder = opendir((get_env(env, "HOME"))->val)))
		return (FAILURE);*/
	if (!(chdir((get_env(env, "HOME"))->val)))
	{
		update_env_pwd(env, command);
		if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mcurrent working dir: %s\n", g_shell.cwd);
		return (SUCCESS);
	}
	else //try unset HOME
	{
		ft_dprintf(STDERR_FILENO, "minig_shell: cd: ");
		ft_perror((get_env(env, "HOME"))->val);
		return (FAILURE);
	}
}

static int	changedir_path(t_list *env, t_list *command)
{
	if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mchange working dir: %s\n", ((t_token*)command->next->content)->text);
	if (!(chdir(((t_token*)command->next->content)->text)))
	{
		update_env_pwd(env, command);
		if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mcurrent working dir: %s\n", g_shell.cwd);
		return (SUCCESS);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "minig_shell: cd: ");
		ft_perror(((t_token*)command->next->content)->text);
		return (FAILURE);
	}
}

int			btin_cd(t_list *command)
{
	t_list	*env;

	env = g_shell.env;
	if (!((t_token*)command->next))
		return (changedir_home(env, command));
	else
		return (changedir_path(env, command));
}
