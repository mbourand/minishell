/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 13:58:42 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/04 16:30:38 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_path(t_env *env)
{
	char	**paths;

	if (!env)
		return (NULL);
	paths = ft_split(env->val, ':');
	return (paths);
}

char	*search_in_dir(DIR *dir, char *name, char *dirname)
{
	struct dirent	*entry;
	char			*filepath;
	char			*tmp;

	while ((entry = readdir(dir)))
	{
		if (!ft_strcmp(entry->d_name, "..") || !ft_strcmp(entry->d_name, "."))
			continue ;
		if (!ft_strcmp(entry->d_name, name))
		{
			filepath = ft_strjoin(dirname, "/");
			tmp = filepath;
			filepath = ft_strjoin(filepath, entry->d_name);
			ft_free(&tmp);
			return (filepath);
		}
	}
	return (NULL);
}

char	*find_exe(char **path, char *name)
{
	size_t	i;
	DIR		*dir;
	char	*exec_path;

	i = 0;
	while (path[i])
	{
		if (!(dir = opendir(path[i])))
			break ;
		errno = 0;
		if ((exec_path = search_in_dir(dir, name, path[i])))
		{
			ft_memdel((void**)&dir);
			return (exec_path);
		}
		if (errno != 0)
			exit(1);
		i++;
		ft_memdel((void**)&dir);
	}
	return (NULL);
}
