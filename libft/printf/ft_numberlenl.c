/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numberlenl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 11:32:16 by mbourand          #+#    #+#             */
/*   Updated: 2019/12/09 11:32:26 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		number_lenl(unsigned long n, unsigned int base_len)
{
	unsigned long	tmp;
	int				len;

	tmp = n;
	len = 1;
	while (tmp >= base_len)
	{
		len++;
		tmp /= base_len;
	}
	return (len);
}
