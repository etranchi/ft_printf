/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 17:08:39 by Etienne           #+#    #+#             */
/*   Updated: 2017/09/16 17:08:41 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*check_djz_modifiers(t_modifiers *m, va_list params, char c)
{
	char *buffer;

	if (m->l == 1 || c == 'D')
		buffer = ft_lltoa(va_arg(params, long));
	else if (m->j && c != 'D')
		buffer = ft_lltoa(va_arg(params, intmax_t));
	else if (m->z && c != 'D')
		buffer = ft_lltoa(va_arg(params, size_t));
	else
		buffer = ft_itoa(va_arg(params, int));
	return (buffer);
}

char	*check_d_modifiers(t_modifiers *m, va_list params, char c)
{
	char	*buffer;
	int		tmp;

	if (m->ll && c != 'D')
		buffer = ft_lltoa(va_arg(params, long long));
	else if (m->hh && c != 'D')
	{
		if (!(tmp = (char)va_arg(params, int)))
			buffer = ft_strdup("0");
		else if (ft_strcmp((buffer = ft_itoa(tmp)), "128") == 0)
			buffer = ft_strdup("-128");
	}
	else if (m->h && c != 'D')
	{
		if (!(tmp = (short)va_arg(params, int)))
			buffer = ft_strdup("0");
		else if (ft_strcmp((buffer = ft_itoa(tmp)), "32768") == 0)
			buffer = ft_strdup("-32768");
	}
	else
		buffer = check_djz_modifiers(m, params, c);
	return (buffer);
}

char	*check_x_modifiers(t_modifiers *m, va_list params, char c)
{
	char *buffer;
	char *b;

	b = (c == 'x') ? ft_strdup("0123456789abcdef") :
	ft_strdup("0123456789ABCDEF");
	if (m->l)
		buffer = ft_llutoa_base(va_arg(params, unsigned long), b);
	else if (m->ll)
		buffer = ft_llutoa_base(va_arg(params, unsigned long long), b);
	else if (m->h)
		buffer = ft_llutoa_base((unsigned short)va_arg(params, unsigned int),
			b);
	else if (m->hh)
		buffer = ft_llutoa_base((unsigned char)va_arg(params, unsigned int), b);
	else if (m->j)
		buffer = ft_lutoa_base(va_arg(params, uintmax_t), b);
	else if (m->z)
		buffer = ft_lutoa_base(va_arg(params, size_t), b);
	else
		buffer = ft_llutoa_base(va_arg(params, unsigned int), b);
	free(b);
	return (buffer);
}

char	*check_o_modifiers(t_modifiers *m, va_list params, char c)
{
	char *buffer;
	char *base;

	base = ft_strdup("01234567");
	if (m->l || c == 'O')
		buffer = ft_llutoa_base(va_arg(params, unsigned long), base);
	else if (m->ll)
		buffer = ft_llutoa_base(va_arg(params, unsigned long long), base);
	else if (m->h)
		buffer = ft_llutoa_base((unsigned short)va_arg(params,
			unsigned int), base);
	else if (m->hh)
		buffer = ft_llutoa_base((unsigned char)va_arg(params,
			unsigned int), base);
	else if (m->j)
		buffer = ft_llutoa_base(va_arg(params, uintmax_t), base);
	else if (m->z)
		buffer = ft_llutoa_base(va_arg(params, size_t), base);
	else
		buffer = ft_uitoa_base(va_arg(params, unsigned int), base);
	free(base);
	return (buffer);
}

char	*check_u_modifiers(t_modifiers *m, va_list params, char c)
{
	char *buffer;

	if (m->l || c == 'U')
		buffer = ft_llutoa(va_arg(params, unsigned long long));
	else if (m->ll)
		buffer = ft_llutoa(va_arg(params, unsigned long long));
	else if (m->h)
		buffer = ft_llutoa((unsigned short)va_arg(params, unsigned int));
	else if (m->hh)
		buffer = ft_llutoa((unsigned char)va_arg(params, unsigned int));
	else if (m->j)
		buffer = ft_llutoa(va_arg(params, uintmax_t));
	else if (m->z)
		buffer = ft_llutoa(va_arg(params, size_t));
	else
		buffer = ft_llutoa(va_arg(params, unsigned int));
	return (buffer);
}

char	*check_p_modifiers(t_modifiers *m, va_list params)
{
	char *buffer;

	if (m->l)
		buffer = ft_llutoa_base(va_arg(params, unsigned long),
			"0123456789abcdef");
	else
		buffer = ft_llutoa_base(va_arg(params, unsigned long long),
			"0123456789abcdef");
	return (buffer);
}

int		check_c_modifiers(t_modifiers *m, char c)
{
	if (c == 'c' && m->l == 0)
		return (1);
	else
		return (0);
}

void	check_s_modifiers(t_conv *cv, t_modifiers *m, va_list params, char c)
{
	cv->buffer_nb = NULL;
	cv->buffer_wnb = NULL;
	if (m->l || c == 'S')
	{
		cv->buffer_wnb = va_arg(params, wchar_t*);
	}
	else
	{
		cv->buffer_nb = va_arg(params, char*);
	}
}
