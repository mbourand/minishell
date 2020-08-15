/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 14:57:45 by nforay            #+#    #+#             */
/*   Updated: 2020/08/16 01:08:01 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_pwd(t_list *env, t_shell *shell)
{
	char	buf[PATH_MAX];

	shell->cwd = getcwd(buf, PATH_MAX);
	free((get_env(env, "OLDPWD"))->val);
	(get_env(env, "OLDPWD"))->val = (get_env(env, "PWD"))->val;
	(get_env(env, "PWD"))->val = ft_strdup(shell->cwd);
}

static int	changedir_home(t_list *env, t_shell *shell)
{
	//DIR		*folder; //Maybe unnecessary to try open before chdir
	if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mchange working dir: %s\n", (get_env(env, "HOME"))->val);
	/*if (!(folder = opendir((get_env(env, "HOME"))->val)))
		return (FAILURE);*/
	if (!(chdir((get_env(env, "HOME"))->val)))
	{
		update_env_pwd(env, shell);
		if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mcurrent working dir: %s\n", shell->cwd);
		return (SUCCESS);
	}
	else //try unset HOME
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: ");
		ft_perror((get_env(env, "HOME"))->val);
		return (FAILURE);
	}
}

static int	changedir_path(t_list *env, t_shell *shell, t_list *command)
{
	if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mchange working dir: %s\n", ((t_token*)command->next->content)->text);
	if (!(chdir(((t_token*)command->next->content)->text)))
	{
		update_env_pwd(env, shell);
		if (DEBUG) ft_printf("\e[31m[DEBUG]\e[39mcurrent working dir: %s\n", shell->cwd);
		return (SUCCESS);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: ");
		ft_perror(((t_token*)command->next->content)->text);
		return (FAILURE);
	}
}

int			btin_cd(t_shell *shell, t_list *command)
{
	t_list	*env;

	env = shell->env;
	if (!((t_token*)command->next))
		return (changedir_home(env, shell));
	else
		return (changedir_path(env, shell, command));
}
