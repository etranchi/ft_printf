/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 14:56:30 by etranchi          #+#    #+#             */
/*   Updated: 2017/09/06 14:56:32 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_lllen(long long nb)
{
	int i;

	i = 1;
	while (nb /= 10)
		i++;
	return (i);
}

int		ft_ulllen(unsigned long long nb)
{
	int i;

	i = 1;
	while (nb /= 10)
		i++;
	return (i);
}

int		ft_uintlen(unsigned long long nb)
{
	int i;

	i = 1;
	while (nb /= 10)
		i++;
	return (i);
}

int		ft_intlen(unsigned long long nb)
{
	int i;

	i = 1;
	while (nb /= 10)
		i++;
	return (i);
}

char	*ft_lltoa(long long nb)
{
	char	*str;
	int		sign;
	int		len;

	sign = 0;
	if ((unsigned long long)nb == -9223372036854775808ull)
		return (ft_strdup("-9223372036854775808"));
	if ((long long)nb < 0 && nb != 2147483648)
	{
		sign = 1;
		nb = -nb;
	}
	len = ft_lllen(nb) + sign;
	str = malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (len--)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}

char	*ft_llutoa(unsigned long long nb)
{
	char	*str;
	int		len;

	len = ft_ulllen(nb);
	str = malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (len--)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (str);
}

char	*ft_uitoa(unsigned int nb)
{
	char	*str;
	int		len;

	len = ft_uintlen(nb);
	str = malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (len--)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (str);
}

char	*ft_itoa(int nb)
{
	char	*str;
	int		sign;
	int		len;

	sign = 0;
	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	if (nb < 0)
	{
		sign = 1;
		nb = -nb;
	}
	len = ft_intlen(nb) + sign;
	str = malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (len--)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}

int		ui_base_len(unsigned int nb, unsigned int base)
{
	int i;

	i = 1;
	while (nb /= base)
		i++;
	return (i);
}

char	*ft_uitoa_base(unsigned int nb, char *base)
{
	char	*str;
	int		len;

	len = ui_base_len(nb, ft_strlen(base));
	str = malloc(sizeof(char) * (len + 1));
	str[len--] = '\0';
	while ((nb / ((unsigned int)ft_strlen(base))) > 0)
	{
		str[len--] = base[nb % ft_strlen(base)];
		nb /= ft_strlen(base);
	}
	str[len] = base[nb % ft_strlen(base)];
	return (str);
}

int		int_base_len(int nb, int base)
{
	int i;

	i = 1;
	while (nb /= base)
		i++;
	return (i);
}

char	*ft_itoa_base(unsigned int nb, char *base)
{
	char	*str;
	int		len;
	int		sign;

	sign = 0;
	len = int_base_len(nb, ft_strlen(base));
	str = malloc(sizeof(char) * (len + 1));
	str[len--] = '\0';
	while (nb / ft_strlen(base) > 0)
	{
		str[len--] = base[nb % (int)ft_strlen(base)];
		nb /= (int)ft_strlen(base);
	}
	return (str);
}

int		ull_base_len(unsigned long long nb, unsigned int base)
{
	int i;

	i = 1;
	while (nb /= base)
		i++;
	return (i);
}

char	*ft_lutoa_base(unsigned long n, char *base)
{
	char				*str;
	int					len;
	unsigned long long	nb;

	nb = (unsigned long long)n;
	len = ull_base_len(nb, ft_strlen(base));
	str = malloc(sizeof(char) * (len + 1));
	str[len--] = '\0';
	while (nb / (unsigned long long)ft_strlen(base) > 0)
	{
		str[len--] = base[nb % ft_strlen(base)];
		nb /= ft_strlen(base);
	}
	str[len] = base[nb % ft_strlen(base)];
	return (str);
}

char	*ft_llutoa_base(unsigned long long nb, char *base)
{
	char	*str;
	int		len;

	if (nb == 4294967296 && ft_strcmp(base, "023456789abcdef") == 0)
		return (ft_strdup("100000000"));
	if (nb == 4294967296 && ft_strcmp(base, "023456789ABCDEF") == 0)
		return (ft_strdup("0"));
	len = ull_base_len(nb, ft_strlen(base));
	str = malloc(sizeof(char) * (len + 1));
	str[len--] = '\0';
	while (nb / (unsigned long long)ft_strlen(base) > 0)
	{
		str[len--] = base[nb % ft_strlen(base)];
		nb /= ft_strlen(base);
	}
	str[len] = base[nb % ft_strlen(base)];
	return (str);
}

char	*ft_strjoin_free(char **s1, char **s2, int bool_s1, int bool_s2)
{
	char	*str;
	int		i;
	int		j;

	str = ft_strnew(ft_strlen(*s1) + ft_strlen(*s2));
	i = 0;
	j = 0;
	while ((*s1) && (*s1)[i])
	{
		str[i] = (*s1)[i];
		i++;
	}
	if ((*s1) && bool_s1)
		ft_memdel((void **)s1);
	while ((*s2) && (*s2)[j])
	{
		str[i] = (*s2)[j];
		j++;
		i++;
	}
	if ((*s2) && bool_s2)
		ft_memdel((void **)s2);
	return (str);
}


int		ft_atoi_bit_rev(const char *str)
{
	int		result;
	int		i;
	int		p;

	i = 0;
	p = 1;
	result = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '1')
			result = result + p;
		i++;
		p = p * 2;
	}
	return (result);
}
