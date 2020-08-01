/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 02:48:06 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/26 02:48:06 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_prompt(t_shell *shell)
{
	ft_printf("minishell:%s$ ", (get_env(shell->env, "PWD"))->val);
}