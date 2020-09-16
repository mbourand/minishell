/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:32:41 by nforay            #+#    #+#             */
/*   Updated: 2020/09/16 14:00:09 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_perror(char *s)
{
	char	*errstr;
	char	*prefix;

	errstr = strerror(errno);
	if (!s || *s == '\0')
		prefix = "";
	else
		prefix = ": ";
	ft_dprintf(2, "%s%s%s\n", s, prefix, errstr);
}

t_range		*new_range(size_t min, size_t max)
{
	t_range	*range;

	if (!(range = malloc(sizeof(t_range))))
		exit(1);
	range->min = min;
	range->max = max;
	return (range);
}

static void	init_shell_level(void)
{
	t_list	*new;

	if (!(new = ft_lstnew(parse_env("SHLVL=1"))))
		exit(1);
	ft_lstadd_back(&g_shell.env, new);
}

void		set_shell_level(void)
{
	char	*str;
	char	*ptr;

	if (get_env(g_shell.env, "SHLVL"))
	{
		str = (get_env(g_shell.env, "SHLVL"))->val;
		ptr = str;
		while (ft_isdigit(*ptr))
			ptr++;
		if (*ptr == '\0')
		{
			ptr = ft_itoa(ft_atoi(str) + 1);
			free(str);
			(get_env(g_shell.env, "SHLVL"))->val = ptr;
		}
		else
		{
			free(str);
			(get_env(g_shell.env, "SHLVL"))->val = ft_strdup("1");
		}
	}
	else
		init_shell_level();
}

void		free_env(t_env *env)
{
	ft_free(&(env->key));
	ft_free(&(env->val));
	ft_memdel((void**)&(env));
}
