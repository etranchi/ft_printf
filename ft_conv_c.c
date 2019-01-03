/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 18:51:11 by Etienne           #+#    #+#             */
/*   Updated: 2017/09/18 18:51:12 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	create_c_buffer(t_conv *cv, t_env *e, int len)
{
	cv->mode = 0;
	if (e->buff_len > e->pre && e->buff_len > len)
	{
		cv->mode = 1;
		cv->buffer_str = malloc(sizeof(char) * (e->buff_len + 1));
		cv->buffer_str[e->buff_len] = '\0';
		if (e->pre > 0)
			cv->buffer_nb[e->pre] = '\0';
		ft_memset(cv->buffer_str, cv->empty, e->buff_len);
	}
	else if (e->pre > e->buff_len)
	{
		cv->mode = 2;
		cv->buffer_str = malloc(sizeof(char) * (e->pre + 1));
		cv->buffer_str[e->pre] = '\0';
	}
	else
	{
		cv->mode = 0;
		cv->buffer_str = malloc(sizeof(char) * (2));
		cv->buffer_str[1] = '\0';
		ft_memset(cv->buffer_str, cv->empty, 1);
	}
}

void	fill_c_buffer(t_env *e, t_conv *cv, int nb)
{
	int i;

	i = -1;
	if (e->flags->minus == 0)
	{
		while (++i < ((int)ft_strlen(cv->buffer_str) - 1))
			write(1, &cv->buffer_str[i], 1);
		ft_putchar(nb);
	}
	else
	{
		ft_putchar(nb);
		while (++i < ((int)ft_strlen(cv->buffer_str) - 1))
			write(1, &cv->buffer_str[i], 1);
	}
}

int print_wchar(va_list params)
{
	wchar_t buffer;
	int len;
	char *buff;
	char *bu;

	len = 0;
	buff = NULL;
	bu = NULL;
	buffer = va_arg(params, wchar_t);
	return (len);
}

int		go_to_simple_c(va_list params, t_conv *cv, t_env *e)
{
	unsigned int	arg;

	arg = va_arg(params, int);
	create_c_buffer(cv, e, 1);
	fill_c_buffer(e, cv, arg);
	if (arg == 0 && ft_strlen(cv->buffer_str) == 0)
		return (1);
	else
		return (0);
}

int		go_to_complicate_c(va_list params, t_conv *cv, t_env *e)
{
	unsigned int	arg;
	int				len;

	len = 0;
	arg = va_arg(params, unsigned int);
	if (arg == 0)
	{
		len++;
		cv->buffer_str = NULL;
	}
	create_c_buffer(cv, e, len);
	fill_c_buffer(e, cv, arg);
	len = (len > 1) ? (int)ft_strlen(cv->buffer_str) : (int)ft_strlen(cv->buffer_str) - len;
	return (len);
}

void	init_cv_c(t_env *e, t_conv *cv, char c)
{
	cv->empty = (e->flags->zero) ? '0' : ' ';
	cv->buffer_len = 0;
	cv->buffer_len = check_c_modifiers(e->modifiers, c);
}

int		ft_conv_c(t_env *e, va_list params, char c)
{
	t_conv			*cv;
	int				len;
	wchar_t			tmp;

	len = 0;
	cv = malloc(sizeof(t_conv));
	init_cv_c(e, cv, c);
	if (c == 'c' && e->modifiers->l == 0)
	{
		if (go_to_simple_c(params, cv, e))
			return (1);
		len += ft_strlen(cv->buffer_str);
	}
	else
	{
		cv->buffer_str = malloc(4);
		if((tmp = va_arg(params, wchar_t)) == 0)
		{
			if(e->modifiers->hh == 0 && e->flags->space == 0)
			{
				return (1);
			}
			else	
			{
				return (ft_putwchar(tmp, cv->buffer_str));
			}
		}
		len = ft_putwchar(tmp, cv->buffer_str);
	}
	free(cv->buffer_str);
	free(cv);
	return (len);
}
