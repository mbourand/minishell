/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourand <mbourand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:54:26 by mbourand          #+#    #+#             */
/*   Updated: 2020/07/06 16:03:30 by mbourand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

typedef struct	s_arg
{
	int			zero;
	int			minus;
	int			precision;
	int			mfw;
	int			dot;
	char		conv;
	char		c;
}				t_arg;

int				ft_printf(char const *format, ...);
int				print_int(t_arg arg, int i);
int				print_char(t_arg arg, char i);
int				print_string(t_arg arg, char *i);
int				print_unsigned_int(t_arg arg, unsigned int i);
int				print_hex(t_arg arg, unsigned int i);
int				print_pointer(t_arg arg, unsigned long i);
void			ft_putunsignednbr_fd(unsigned int u, int fd);
char			*ft_tobase(unsigned long n, char *base);
int				print_mfw(t_arg arg, int expected_minus,
				long len, int negative);
int				print_mfw_string(t_arg arg, int expected_minus,
				long len);
int				print_mfw_char(t_arg arg, int expected_minus);
int				number_len(long nb, unsigned int base_len);
int				print_mfw_pointer(t_arg arg, int expected_minus, long len,
				int negative);
int				number_lenl(unsigned long nb, unsigned int base_len);
int				skip_charset(const char *s, const char *charset);
int				ft_abs(int i);
int				get_arg(char const *format, t_arg *arg, va_list ap);
void			reset_arg(t_arg *arg);

#endif
