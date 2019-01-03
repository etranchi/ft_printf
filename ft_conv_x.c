/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 18:39:39 by Etienne           #+#    #+#             */
/*   Updated: 2017/09/17 18:39:40 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	create_x_buffer(t_conv *cv, t_env *e)
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

void	diez_mode_bis(t_env *e, t_conv *cv, char *tmp)
{
	int i;

	i = 0;
	if (e->flags->zero)
	{
		cv->buffer_str[0] = tmp[0];
		cv->buffer_str[1] = tmp[1];
	}
	else
	{
		i = ft_strlen(cv->buffer_str) - ft_strlen(cv->buffer_nb);
		cv->buffer_str[i - 2] = tmp[0];
		cv->buffer_str[i - 1] = tmp[1];
	}
}

void	diez(t_env *e, t_conv *cv, char c)
{
	char *tmp;

	tmp = (c == 'x') ? ft_strdup("0x") : ft_strdup("0X");
	if (ft_strlen(cv->buffer_str) > ft_strlen(cv->buffer_nb) && e->flags->minus)
	{
		cv->buffer_str[0] = tmp[0];
		cv->buffer_str[1] = tmp[1];
	}
	else if (ft_strlen(cv->buffer_str) > ft_strlen(cv->buffer_nb) &&
		!e->flags->minus)
		diez_mode_bis(e, cv, tmp);
	else if (ft_strlen(cv->buffer_nb) == ft_strlen(cv->buffer_str))
		cv->buffer_str = ft_strjoin(tmp, cv->buffer_nb);
}

void	fill_modex_d(t_conv *cv, int diez, int pre, char *tmp)
{
	int i;
	int j;

	i = -1;
	j = (int)ft_strlen(cv->buffer_str) - (int)ft_strlen(cv->buffer_nb) - 1;
	if (diez == 1 && ft_strcmp("0", cv->buffer_nb) != 0 && cv->empty == ' ')
	{
		cv->buffer_str[j] = tmp[1];
		cv->buffer_str[j - 1] = tmp[0];
	}
	else if (diez == 1 && ft_strcmp("0", cv->buffer_nb) != 0
		&& cv->empty == '0')
	{
		cv->buffer_str[1] = tmp[1];
		cv->buffer_str[0] = tmp[0];
	}
	if(pre > (int)ft_strlen(cv->buffer_nb))
	{
		j -= (pre - (int)ft_strlen(cv->buffer_nb));
		while ((pre - cv->buffer_len) > 0 && ++i < pre - cv->buffer_len)
			cv->buffer_str[++j] = '0';
		j -= 2;
	}
	i = -1;
	while (cv->buffer_nb[++i])
		cv->buffer_str[++j] = cv->buffer_nb[i];
}

void	fill_modex_t(t_conv *cv, int diez, char *tmp)
{
	char	*tmp1;
	int		i;
	int		j;

	i = -1;
	j = ft_strlen(cv->buffer_str) - ft_strlen(cv->buffer_nb);
	while (cv->buffer_nb[++i])
		cv->buffer_str[j++] = cv->buffer_nb[i];
	if (diez == 1 && ft_strcmp("0", cv->buffer_nb) != 0)
	{
		tmp1 = cv->buffer_str;
		cv->buffer_str = ft_strjoin(tmp, cv->buffer_str);
		free(tmp1);
	}
}

void	fill_x_buffer(t_conv *cv, int diez, int pre, char c)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp1;

	i = -1;
	j = -1;
	tmp = (c == 'x') ? ft_strdup("0x") : ft_strdup("0X");
	if (cv->mode == 1)
		fill_modex_d(cv, diez, pre, tmp);
	if (cv->mode == 2)
		fill_modex_t(cv, diez, tmp);
	if (cv->mode == 0)
	{
		while (cv->buffer_nb[++i] != '\0')
			cv->buffer_str[i] = cv->buffer_nb[i];
		if (diez == 1 && ft_strcmp("0", cv->buffer_nb) != 0)
		{
			tmp1 = cv->buffer_str;
			cv->buffer_str = ft_strjoin(tmp, cv->buffer_str);
			free(tmp1);
		}
	}
	free(tmp);
}

void	fill_modexm_d(t_conv *cv, int diez, char *tmp)
{
	int i;
	int j;

	i = -1;
	j = 0;
	if (diez == 1 && ft_strcmp("0", cv->buffer_nb) != 0)
	{
		cv->buffer_str[j++] = tmp[0];
		cv->buffer_str[j++] = tmp[1];
	}
	while (cv->buffer_nb[++i])
		cv->buffer_str[j++] = cv->buffer_nb[i];
	while (cv->buffer_str[j])
		cv->buffer_str[j++] = ' ';
}

void	fill_modexm_t(t_conv *cv, int diez, char *tmp)
{
	char	*tmp1;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (cv->buffer_nb[++i])
		cv->buffer_str[j++] = cv->buffer_nb[i];
	if (diez == 1 && ft_strcmp("0", cv->buffer_nb) != 0)
	{
		tmp1 = cv->buffer_str;
		cv->buffer_str = ft_strjoin(tmp, cv->buffer_str);
		free(tmp1);
	}
}

void	fill_x_minus_buffer(t_conv *cv, int diez, char c)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp1;

	i = -1;
	j = -1;
	tmp = (c == 'x') ? ft_strdup("0x") : ft_strdup("0X");
	if (cv->mode == 1)
		fill_modexm_d(cv, diez, tmp);
	if (cv->mode == 2)
		fill_modexm_t(cv, diez, tmp);
	if (cv->mode == 0)
	{
		while (cv->buffer_nb[++i] != '\0')
			cv->buffer_str[i] = cv->buffer_nb[i];
		if (diez == 1 && ft_strcmp("0", cv->buffer_nb) != 0)
		{
			tmp1 = cv->buffer_str;
			cv->buffer_str = ft_strjoin(tmp, cv->buffer_str);
			free(tmp1);
		}
	}
	free(tmp);
}

int		ft_conv_x(t_env *e, va_list params, char c)
{
	t_conv	*cv;
	int		len;

	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	cv->buffer_nb = check_x_modifiers(e->modifiers, params, c);
	if (e->flags->point == 1 && e->pre == 0)
		cv->buffer_nb = NULL;
	create_x_buffer(cv, e);
	if (cv->buffer_nb != NULL)
	{
		if (e->flags->minus == 1)
			fill_x_minus_buffer(cv, e->flags->diez, c);
		else
			fill_x_buffer(cv, e->flags->diez, e->pre, c);
	}
	ft_putstr(cv->buffer_str);
	len = (int)ft_strlen(cv->buffer_str);
	free(cv->buffer_str);
	free(cv->buffer_nb);
	free(cv);
	return (len);
}
