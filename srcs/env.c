/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 18:53:04 by mbourand          #+#    #+#             */
/*   Updated: 2020/09/15 02:49:13 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*parse_env(char *str)
{
	t_env	*env;

	if (!(env = malloc(sizeof(t_env) * 1)))
		exit(1);
	env->key = ft_strjoinuntil("", str, '=');
	str += ft_strlen(env->key) + 1;
	env->val = ft_strjoin("", str);
	return (env);
}

t_list	*init_env(char **env)
{
	size_t	i;
	t_list	*ret;
	t_list	*new;

	if (!env)
		return (NULL);
	i = 0;
	ret = 0;
	while (env[i])
	{
		if (!(new = ft_lstnew(parse_env(env[i]))))
			exit(1);
		ft_lstadd_back(&ret, new);
		i++;
	}
	return (ret);
}

t_env	*get_env(t_list *env, char *key)
{
	t_env	*content;
	size_t	len;

	if (!key)
		return (NULL);
	while (env)
	{
		content = (t_env*)env->content;
		len = ft_strlen(key) > ft_strlen(content->key) ? ft_strlen(key)
			: ft_strlen(content->key);
		if (!(ft_strncmp(key, content->key, len)))
			return (content);
		env = env->next;
	}
	return (NULL);
}

char	*get_var_name(char *str)
{
	char	*name;
	int		digits;
	size_t	i;

	if (!str)
		return (NULL);
	name = NULL;
	i = 0;
	digits = ft_isdigit(str[0]);
	while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
	{
		if (digits && !ft_isdigit(str[i]))
			break ;
		ft_straddchar(&name, str[i], 1);
		i++;
	}
	return (name);
}
