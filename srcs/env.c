/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 18:53:04 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/17 18:53:04 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_env	*parse_env(char *str)
{
	t_env* env;

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