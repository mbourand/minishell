/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numberlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 11:32:13 by mbourand          #+#    #+#             */
/*   Updated: 2019/12/09 11:32:14 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		number_len(long n, unsigned int base_len)
{
	unsigned long	tmp;
	int				len;

	tmp = (n < 0 ? -n : n);
	len = 1 + (n < 0);
	while (tmp >= base_len)
	{
		len++;
		tmp /= base_len;
	}
	return (len);
}
