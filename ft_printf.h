/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:32:27 by etranchi          #+#    #+#             */
/*   Updated: 2017/08/31 17:33:01 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define UINT_MAX 4294967295;

# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <wchar.h>
# include <stdlib.h>
# include <limits.h>
typedef struct s_flags
{
	int diez;
	int minus;
	int plus;
	int space;
	int point;
	int zero;
}			t_flags;

typedef struct s_modifiers
{
	int h;
	int l;
	int hh;
	int ll;
	int j;
	int z;
}				t_modifiers;

typedef struct s_types
{
	int s;
	int S;
	int u;
	int U;
	int d;
	int D;
	int x;
	int X;
	int c;
	int C;
	int p;
	int i;
}			t_types;

typedef struct s_conv
{
	char *buffer_nb;
	wchar_t *buffer_wnb;
	char *buffer_str;
	int buffer_len;
	int mode;
	char empty;
	char sign;
}				t_conv;

typedef struct s_env
{
	char *fmt;
	char *buffer;
	int len;
	int buff_len;
	int pre;
	t_flags *flags;
	t_modifiers *modifiers;
	t_types  *types;
}				t_env;

typedef struct	s_octect
{
	unsigned int	u;
	unsigned int	d;
	unsigned int	t;
	unsigned int	q;
}				t_octet;

int		get_precision(t_env *e, int i, int *len);
int		get_buff_len(t_env *e, int i, int *len);
void	init_env(t_env *e, const char *format);
int 	is_flag(char *str, int i);
int 	is_modifier(char *str, int i);
int 	is_type(char c);
int		set_modifiers(t_modifiers *modifiers, char *fmt, int i);
void 	set_flags(t_flags *flags, char *fmt, int i);
int		set_type(t_env *e, char c, va_list params);
int 	set_pourcent(t_env *e, char c);

void 	init_flags_modi(t_flags *flags, t_modifiers *modifiers);
int ft_conv_s(t_env *e, va_list params, char c);
int ft_conv_c(t_env *e, va_list params, char c);
int ft_conv_p(t_env *e, va_list params);

char *ft_lutoa_base(unsigned long n, char *base);
char *ft_itoa_base(unsigned int nb, char *base);
char *ft_lltoa_base(long long nb, char *base);
char *ft_llutoa_base(unsigned long long nb, char *base);
char *ft_lltoa(long long nb);
char *ft_llutoa(unsigned long long nb);
int ft_conv_dec(t_env *e, va_list params, char c);
int ft_conv_u(t_env *e, va_list params, char c);
int ft_conv_x(t_env *e, va_list params, char c);
int ft_conv_o(t_env *e, va_list params, char c);
char	*check_sign(t_conv *cv);

void create_d_buffer(t_conv *cv, t_env *e);
void create_s_buffer(t_conv *cv, t_env *e);
char *ft_uitoa_base(unsigned int nb, char *base);
char *ft_uitoa(unsigned int nb);
char *ft_itoa( int nb);
void f_fill_buff(t_conv *cv, int f_plus, int pre, int space);
void fill_d_minus(t_conv *cv, int f_plus, int pre, int f_space);
void fill_s_buffer(t_conv *cv, int pre);
void fill_s_minus(t_conv *cv, int pre);
void fill_x_buffer(t_conv *cv, int diez, int pre, char c);
void fill_o_minus(t_conv *cv, t_flags *flags, int pre);
void fill_o_buffer(t_conv *cv, int f_plus, int pre);
void create_x_buffer(t_conv *cv, t_env *e);
char		*ft_strjoin_free(char **s1, char **s2, int bool_s1, int bool_s2);

char	*wchar_handler_ext(wchar_t chr);
int		ft_putwchar(wchar_t w, char *n);
int	ft_size_bin(unsigned int value);
int			ft_wlen(unsigned int w);
char	*ft_mask1(wchar_t n);
char	*ft_mask2(wchar_t n);
char	*ft_mask3(wchar_t n);
char	*ft_mask4(wchar_t n);

// Check Modifiers
char *check_d_modifiers(t_modifiers *m, va_list params, char c);
void check_s_modifiers(t_conv *cv, t_modifiers *m, va_list params, char c);
char *check_u_modifiers(t_modifiers *m, va_list params, char c);
char *check_x_modifiers(t_modifiers *m, va_list params, char c);
char *check_o_modifiers(t_modifiers *m, va_list params, char c);
int check_c_modifiers(t_modifiers *m, char c);
char *check_p_modifiers(t_modifiers *m, va_list params);

void free_cv(t_conv *cv);

#endif
