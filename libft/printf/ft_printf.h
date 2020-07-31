/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforay <nforay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:08:26 by nforay            #+#    #+#             */
/*   Updated: 2020/07/31 17:02:43 by nforay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>

enum	e_state
{
	LETTER,
	FLAG,
	CONV,
	ERROR,
	END
};

# define F_HH		"hh"
# define F_LL		"ll"
# define F_MINUS	"-"
# define F_ZERO		"0"
# define F_ASTER	"*"
# define F_HASH		"#"
# define F_SPACE	" "
# define F_PLUS		"+"
# define F_H		"h"
# define F_L		"l"
# define F_POINT	"."
# define ALLCONV	"cspdiuxX%nfge"
# define B_TEN		"0123456789"
# define B_HEX		"0123456789abcdef"
# define B_MHEX		"0123456789ABCDEF"
# define NB_FLAG	11
# define NB_CONV	13
# define TRUE		1
# define FALSE		0

# define HH			0x000001
# define LL			0x000002
# define MINUS		0x000004
# define ZERO		0x000008
# define ASTER		0x000010
# define HASH		0x000020
# define SPACE		0x000040
# define PLUS		0x000080
# define H			0x000100
# define L			0x000200
# define POINT		0x000400

# define C_CONV		0x0001000
# define S_CONV		0x0002000
# define P_CONV		0x0004000
# define D_CONV		0x0008000
# define I_CONV		0x0010000
# define U_CONV		0x0020000
# define X_CONV		0x0040000
# define XMAJ_CONV	0x0080000
# define PER_CONV	0x0100000
# define N_CONV		0x0200000
# define F_CONV		0x0400000
# define G_CONV		0x0800000
# define E_CONV		0x1000000

typedef struct				s_args
{
	char					c;
	char					*s;
	unsigned long			p;
	int						d;
	unsigned int			ux;
	int						*n;
	signed char				hhd;
	unsigned char			hhux;
	signed char				*hhn;
	long long int			lld;
	unsigned long long int	llux;
	long long int			*lln;
	short int				hd;
	unsigned short int		hux;
	short int				*hn;
	long int				ld;
	unsigned long int		lux;
	long int				*ln;
}							t_args;

typedef struct				s_state_machine
{
	enum e_state			state;
	char					buffer[4096];
	int						len;
	char					*out;
	int						flag;
	int						fwidth;
	int						preci;
	int						fd;
	t_args					args;
	va_list					params;
}							t_state_machine;

typedef int	(*t_function)(const char *, t_state_machine *);

int							ft_printf(const char *format, ...);
int							ft_dprintf(int fd, const char *format, ...);
void						extract_aste(t_state_machine *m);
void						print_perc(t_state_machine *m);
void						print_conv(t_state_machine *m);
void						print_conv_hh(t_state_machine *m);
void						print_conv_ll(t_state_machine *m);
void						print_conv_h(t_state_machine *m);
void						print_conv_l(t_state_machine *m);
void						print_conv_nolength(t_state_machine *m);
void						print_conv_chr(t_state_machine *m);
void						print_conv_ptr(t_state_machine *m);
void						print_conv_uns(t_state_machine *m);
void						print_conv_uns_hh(t_state_machine *m);
void						print_conv_uns_ll(t_state_machine *m);
void						print_conv_uns_h(t_state_machine *m);
void						print_conv_uns_l(t_state_machine *m);
void						print_conv_chr(t_state_machine *m);
void						print_conv_int(t_state_machine *m);
void						print_conv_int_hh(t_state_machine *m);
void						print_conv_int_ll(t_state_machine *m);
void						print_conv_int_h(t_state_machine *m);
void						print_conv_int_l(t_state_machine *m);
void						print_conv_str(t_state_machine *m);
void						print_conv_n(t_state_machine *m);
int							intlen(int n, int len);
int							get_intlen(int n, int len);
int							get_intlen_hh(signed char n, int len);
int							get_intlen_ll(long long int n, int len);
int							get_intlen_h(short int n, int len);
int							get_intlen_l(long int n, int len);
void						ft_printf_nbr_hhd_fd(signed char n, int size,
							t_state_machine *m);
void						ft_printf_signed_char(signed char n,
							t_state_machine *m);
void						ft_printf_int_h(short int n, t_state_machine *m);
void						ft_printf_nbr_h_fd(short int n, int size,
							t_state_machine *m);
void						ft_printf_int_l(long int n, t_state_machine *m);
void						ft_printf_nbr_l_fd(long int n, int size,
							t_state_machine *m);
void						ft_printf_int_ll(long long int n,
							t_state_machine *m);
void						ft_printf_nbr_ll_fd(long long int n, int size,
							t_state_machine *m);
void						ft_printf_int(int n, t_state_machine *m);
void						ft_printf_nbr_int_fd(int n, int size,
							t_state_machine *m);
int							ft_conv_base_h(t_state_machine *m, int len,
								unsigned short int nbr, char *base);
void						ft_printf_putnbr_base_h(t_state_machine *m,
								unsigned short int nbr, char *base);
void						ft_printf_width_uns_h(t_state_machine *m, int len);
int							ft_conv_base_hh(t_state_machine *m, int len,
							unsigned char nbr,
								char *base);
void						ft_printf_putnbr_base_hh(t_state_machine *m,
								unsigned char nbr, char *base);
void						ft_printf_width_uns_hh(t_state_machine *m, int len);
int							ft_conv_base_l(t_state_machine *m, int len,
								unsigned long int nbr, char *base);
void						ft_printf_putnbr_base_l(t_state_machine *m,
							unsigned long int nbr,
								char *base);
void						ft_printf_width_uns_l(t_state_machine *m, int len);
int							ft_conv_base_ll(t_state_machine *m, int len,
							unsigned long long int nbr,
								char *base);
void						ft_printf_putnbr_base_ll(t_state_machine *m,
							unsigned long long int nbr,
								char *base);
void						ft_printf_width_uns_ll(t_state_machine *m, int len);
int							ft_conv_base(t_state_machine *m, int len,
							unsigned int nbr, char *base);
void						ft_printf_putnbr_base(t_state_machine *m,
							unsigned int nbr, char *base);
void						ft_printf_width_uns(t_state_machine *m, int len);

#endif
