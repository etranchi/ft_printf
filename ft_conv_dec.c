/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_dec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 16:42:28 by etranchi          #+#    #+#             */
/*   Updated: 2017/09/25 15:31:46 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*check_sign(t_conv *cv)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((cv->buffer_nb[i] >= '0' && cv->buffer_nb[i] <= '9') ||
		cv->buffer_nb[i] == '-' || cv->buffer_nb[i] == '+')
		i++;
	cv->buffer_nb[i] = '\0';
	if (cv->buffer_nb[0] == '-')
	{
		cv->sign = '-';
		tmp = cv->buffer_nb;
		cv->buffer_nb = ft_strdup(cv->buffer_nb + 1);
		free(tmp);
		return (cv->buffer_nb);
	}
	else
		cv->sign = '+';
	return (cv->buffer_nb);
}

void	f_minus(t_conv *cv, int pre)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (cv->sign == '-')
		cv->buffer_str[i++] = cv->sign;
	else
		cv->buffer_str[i++] = ' ';
	while (cv->mode && i < pre)
	{
		cv->buffer_str[i] = '0';
		i++;
	}
	while (cv->buffer_nb[j] && cv->buffer_str[i])
	{
		cv->buffer_str[i] = cv->buffer_nb[j];
		i++;
		j++;
	}
}

void	fill_moded_u(t_conv *cv, int f_plus, int space)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp1;

	j = -1;
	i = 0;
	if (cv->sign == '-' || f_plus == 1)
	{
		cv->buffer_str[i++] = cv->sign;
	}
	else if (space == 1)
	{
		tmp = cv->buffer_str;
		tmp1 = ft_strdup(" ");
		cv->buffer_str = ft_strjoin(tmp1, cv->buffer_str);
		free(tmp);
		free(tmp1);
		i++;
	}
	while (cv->buffer_nb[++j])
		cv->buffer_str[i++] = cv->buffer_nb[j];
}

void	fill_moded_d(t_conv *cv, int f_plus, int pre)
{
	int i;
	int j;

	j = -1;
	i = 0;
	if (cv->sign == '-' && !f_plus && cv->empty != '0')
		cv->buffer_str[i - 1] = cv->sign;
	else if ((f_plus == 1 && cv->empty == '0') ||
		(cv->empty == '0' && cv->sign == '-'))
		cv->buffer_str[0] = cv->sign;
	else if (cv->sign == '-')
	{
		cv->buffer_str = ft_strjoin("-", cv->buffer_str);
		i++;
	}
	if (pre > 0)
		while ((pre - cv->buffer_len) > 0 && ++j < (pre - cv->buffer_len))
			cv->buffer_str[i++] = '0';
	j = -1;
	while (cv->buffer_nb[++j])
		cv->buffer_str[i++] = cv->buffer_nb[j];
	if (pre == (int)ft_strlen(cv->buffer_str) && cv->sign == '-')
		cv->buffer_str = ft_strjoin("-", cv->buffer_str);
}

int		moded_t_pre(t_conv *cv, int pre, int f_plus)
{
	int i;
	int j;

	j = -1;
	i = (int)ft_strlen(cv->buffer_str) - pre;
	if (cv->sign == '-' && f_plus == 0 && cv->empty != '0')
		cv->buffer_str[i - 1] = cv->sign;
	while ((pre - cv->buffer_len) > 0 && (pre - ft_strlen(cv->buffer_str)) > 0
		&& ++j < (pre - cv->buffer_len))
		cv->buffer_str[i++] = '0';
	i--;
	return (i);
}

void	fill_moded_t(t_conv *cv, int f_plus, int pre, int i)
{
	int j;

	j = -1;
	if (cv->sign == '-' && f_plus == 0 && cv->empty != '0')
		cv->buffer_str[i] = cv->sign;
	else if ((f_plus == 1 && cv->empty == '0') ||
		(cv->empty == '0' && cv->sign == '-'))
		cv->buffer_str[0] = cv->sign;
	else if (f_plus == 1)
		cv->buffer_str[i - 1] = cv->sign;
	else if ((cv->empty == '0' && cv->sign == '+' && pre > 0)
		|| ft_strcmp("0", cv->buffer_nb) == 0)
		cv->buffer_str[0] = ' ';
	if (pre > (int)ft_strlen(cv->buffer_nb))
	{
		i = moded_t_pre(cv, pre, f_plus);
	}
	j = -1;
	while (cv->buffer_nb[++j])
		cv->buffer_str[++i] = cv->buffer_nb[j];
}

void	f_fill_buff(t_conv *cv, int f_plus, int pre, int space)
{
	if (cv->mode == 0)
		fill_moded_u(cv, f_plus, space);
	if (cv->mode == 2)
		fill_moded_d(cv, f_plus, pre);
	if (cv->mode == 1)
		fill_moded_t(cv, f_plus, pre, ((int)ft_strlen(cv->buffer_str)
			- (int)ft_strlen(cv->buffer_nb) - 1));
}

void	check_width(t_env *e)
{
	int i;

	i = e->buff_len - e->pre;
	while (i-- > 0)
		write(1, " ", 1);
}

void	create_d_buffer(t_conv *cv, t_env *e)
{
	int len;

	len = (cv->buffer_nb) ? ft_strlen(cv->buffer_nb) : 0;
	if (e->buff_len > e->pre && e->buff_len > len)
	{
		cv->mode = 1;
		cv->buffer_str = malloc(sizeof(char) * (e->buff_len + 1));
		cv->buffer_str[e->buff_len] = '\0';
		ft_memset(cv->buffer_str, cv->empty, e->buff_len);
	}
	else if (e->pre > e->buff_len && e->pre > len)
	{
		cv->mode = 2;
		cv->buffer_str = malloc(sizeof(char) * (e->pre + 1));
		cv->buffer_str[e->pre] = '\0';
		ft_memset(cv->buffer_str, '0', e->pre);
	}
	else
	{
		cv->mode = 0;
		cv->buffer_str = malloc(sizeof(char) * (len + 1));
		cv->buffer_str[len] = '\0';
		if (len > 0)
			ft_memset(cv->buffer_str, cv->empty, len);
	}
}

void	fill_d_minus(t_conv *cv, int f_plus, int pre, int f_space)
{
	int i;
	int j;

	i = -1;
	j = -1;
	(void)f_space;
	if (cv->sign == '-' || f_plus == 1)
		cv->buffer_str[++i] = cv->sign;
	if (pre > 0)
	{
		while ((pre - cv->buffer_len) > 0 && ++j < (pre - cv->buffer_len))
			cv->buffer_str[++i] = '0';
	}
	j = -1;
	while (cv->buffer_nb[++j])
		cv->buffer_str[++i] = cv->buffer_nb[j];
	while (cv->buffer_str[++i])
		cv->buffer_str[i] = ' ';
}

void	init_cv_dec(t_env *e, va_list params, t_conv *cv, char c)
{
	cv->empty = (e->flags->zero) ? '0' : ' ';
	cv->buffer_nb = check_d_modifiers(e->modifiers, params, c);
}

void	end_dec_conv(t_conv *cv)
{
	free(cv->buffer_str);
	free(cv->buffer_nb);
	free(cv);
}

int		ft_conv_dec(t_env *e, va_list params, char c)
{
	t_conv	*cv;
	int		len;
	char	*tmp;

	if (!(cv = malloc(sizeof(t_conv))))
		return (-1);
	init_cv_dec(e, params, cv, c);
	if (e->flags->point == 1 && e->pre == 0 &&
		ft_strcmp("0", cv->buffer_nb) == 0)
	{
		tmp = cv->buffer_nb;
		cv->buffer_nb = ft_strdup("");
		free(tmp);
	}
	cv->buffer_nb = check_sign(cv);
	cv->buffer_len = (int)ft_strlen(cv->buffer_nb);
	create_d_buffer(cv, e);
	if (e->flags->minus == 1)
		fill_d_minus(cv, e->flags->plus, e->pre, e->flags->space);
	else
		f_fill_buff(cv, e->flags->plus, e->pre, e->flags->space);
	ft_putstr(cv->buffer_str);
	len = ft_strlen(cv->buffer_str);
	end_dec_conv(cv);
	return (len);
}
