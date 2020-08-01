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

/*
**	Met ce qu'il y a avant le 1er '=' de str dans env->key
**	Et le reste dans env->val (sans le =)
*/
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

/*
**	Remplis l'env à partir du paramètre du main
*/
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

/*
**	Retourne la première variable d'environnement
**	avec le nom key contenue dans l'env
*/
t_env	*get_env(t_list *env, char *key)
{
	t_env	*content;
	size_t	len;

	if (!key)
		return (NULL);
	while (env)
	{
		content = (t_env*)env->content;
		len = ft_strlen(key) > ft_strlen(content->key) ? ft_strlen(key) : ft_strlen(content->key);
		if (!(ft_strncmp(key, content->key, len)))
			return (content);
		env = env->next;
	}
	return (NULL);
}

/*
**	Retourne la chaîne la plus longue respectant les règles
**	de nommage des variables d'environnement
**	Utile pour trouver pour quelle variable d'environnement
**	on doit faire l'expansion
**	Retourne NULL si il n'y a pas de variable d'environnement au nom associé
*/
char	*get_var_name(char *str)
{
	char	*name;
	size_t	i;

	name = NULL;
	i = 0;
	while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_')
	{
		ft_straddchar(&name, str[i], 1);
		i++;
	}
	return (name);
}