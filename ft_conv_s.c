/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:02:41 by etranchi          #+#    #+#             */
/*   Updated: 2017/09/06 15:02:43 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	create_s_buffer(t_conv *cv, t_env *e)
{
	int len;

	len = ft_strlen(cv->buffer_nb);
	if (e->buff_len > e->pre && e->buff_len > len)
	{
		cv->mode = 1;
		cv->buffer_str = malloc(sizeof(char) * (e->buff_len + 1));
		cv->buffer_str[e->buff_len] = '\0';
		ft_memset(cv->buffer_str, cv->empty, e->buff_len);
	}
	else if (e->pre > e->buff_len)
	{
		cv->mode = 2;
		cv->buffer_str = malloc(sizeof(char) * (e->pre + 1));
		cv->buffer_str[e->pre] = '\0';
		ft_memset(cv->buffer_str, cv->empty, e->pre);
		cv->buffer_len = e->buff_len;
	}
	else
	{
		cv->mode = 0;
		if (e->pre)
			len--;
		cv->buffer_str = malloc(sizeof(char) * (len + 1));
		cv->buffer_str[len] = '\0';
		if (len > 0)
			ft_memset(cv->buffer_str, cv->empty, len);
	}
}

void	fill_s_minus(t_conv *cv, int pre)
{
	int i;
	int max;

	i = -1;
	if (cv->mode == 1)
	{
		max = (pre) ? pre : ft_strlen(cv->buffer_nb);
		while (++i < max && cv->buffer_nb[i])
			cv->buffer_str[i] = cv->buffer_nb[i];
	}
	if (cv->mode == 2)
	{
		while (cv->buffer_str[++i])
			cv->buffer_str[i] = cv->buffer_nb[i];
	}
	if (cv->mode == 0)
		ft_strcpy(cv->buffer_str, cv->buffer_nb);
}

void	fill_s_buffer(t_conv *cv, int pre)
{
	int i;
	int j;

	i = -1;
	j = 0;
	if (cv->mode == 1)
	{
		j = ft_strlen(cv->buffer_str);
		if (pre > 0)
			if(pre > (int)ft_strlen(cv->buffer_nb))
	 			j -= pre - (int)ft_strlen(cv->buffer_nb);
	 		else
	 			j -= pre;
	 	else
	 		j -= ft_strlen(cv->buffer_nb);
		i = -1;
		while (cv->buffer_nb[++i] && cv->buffer_str[j])
			cv->buffer_str[j++] = cv->buffer_nb[i];
	}
	if (cv->mode == 2)
	{
		i = (cv->buffer_len > 0 && cv->buffer_len > (int)ft_strlen(cv->buffer_nb)) ? cv->buffer_len - (int)ft_strlen(cv->buffer_nb) : 0;
		while (cv->buffer_str[i] && cv->buffer_nb[j])
			cv->buffer_str[i++] = cv->buffer_nb[j++];
		cv->buffer_str[i] = '\0';
	}
	if (cv->mode == 0)
	{
		j = ft_strlen(cv->buffer_str);
		if (pre > 0)
			j -= pre;
		else
			j -= ft_strlen(cv->buffer_nb);
		while (cv->buffer_nb[++i] && cv->buffer_str[j])
			cv->buffer_str[j++] = cv->buffer_nb[i];
	}
}

void	put_little_s(t_env *e, t_conv *cv, int *len, int nul)
{
	create_s_buffer(cv, e);
	if (e->flags->minus == 1)
		fill_s_minus(cv, e->pre);
	else
		fill_s_buffer(cv, e->pre);
	if (cv->buffer_nb && ft_strcmp("(null)", cv->buffer_nb) == 0 && nul == 1)
		free(cv->buffer_nb);
	ft_putstr(cv->buffer_str);
	*len += ft_strlen(cv->buffer_str);
	free(cv->buffer_str);
}

static int		get_len(wchar_t *str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] > 0 && str[i] <= 128)
			len += 1;
		else if (str[i] > 0 && str[i] <= 2048)
			len += 2;
		else if (str[i] > 0 && str[i] <= 65536)
			len += 3;
		else if (str[i] > 0 && str[i] <= INT_MAX)
			len += 4;
		else
			break ;
		i++;
	}
	return (len);
}

void	put_big_s(t_env *e, t_conv *cv, int *len)
{
	int i;
	int j;

	i = 0;
	cv->buffer_str = ft_strdup("    ");
	if(e->flags->zero && e->flags->point)
	{
		create_s_buffer(cv, e);
		ft_putstr(cv->buffer_str);
		(*len) = ft_strlen(cv->buffer_str);
	}
	else if (cv->buffer_wnb == 0 || cv->buffer_wnb == NULL)
	{
		cv->buffer_nb = ft_strdup("(null)");
		ft_putstr(cv->buffer_nb);
		*len = ft_strlen(cv->buffer_nb);
	}
	else if (cv->buffer_wnb != NULL)
	{
		*len = get_len(cv->buffer_wnb);
		if (e->pre > e->buff_len)
			*len = e->pre - 1;
		if (e->buff_len > e->pre && e->pre)
			(*len) = e->pre;
		if(e->flags->minus == 1)
		{
			j = 0;
			while ((*len) > 0 && j < (*len) && cv->buffer_wnb[j] != 0)
			{
				i += ft_putwchar(cv->buffer_wnb[j], cv->buffer_str);
				j++;
			}
			while((i++) < e->buff_len)
				write(1, &cv->empty, 1);
			(*len) = i - 1;
		}
		else
		{
			while(i < (e->buff_len - (*len)))
			{
				write(1, &cv->empty, 1);
				i++;
			}
			e->buff_len = i;
			i = 0;
			while ((*len) > 0 && i < (*len) && cv->buffer_wnb[i] != 0)
			{
				ft_putwchar(cv->buffer_wnb[i], cv->buffer_str);
				i++;
			}
			(*len) += e->buff_len;
		}
	}
}

int		ft_conv_s(t_env *e, va_list params, char c)
{
	t_conv	*cv;
	int		len;
	int		nul;

	nul = 0;
	cv = malloc(sizeof(t_conv));
	cv->empty = (e->flags->zero) ? '0' : ' ';
	len = 0;
	check_s_modifiers(cv, e->modifiers, params, c);
	if (cv->buffer_nb == NULL && (e->pre > 0 || e->buff_len > 0))
		cv->buffer_nb = ft_strdup("");
	else if (cv->buffer_nb == NULL && e->pre == 0 && (c == 's'
		&& e->modifiers->l == 0))
	{
		cv->buffer_nb = ft_strdup("(null)");
		nul++;
	}
	if (e->flags->point == 1 && e->pre == 0)
		cv->buffer_nb = ft_strdup("");
	if ((e->modifiers->l == 0 && c != 'S'))
		put_little_s(e, cv, &len, nul);
	else
		put_big_s(e, cv, &len);
	free(cv);
	return (len);
}
