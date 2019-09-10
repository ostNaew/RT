/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:30:13 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/20 16:37:01 by ajaehaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long double	ft_atof_integer(char *str)
{
	long double		res;
	long double		sign;
	size_t			i;

	res = 0.;
	i = 0;
	sign = 1.;
	if (str[i] == '-')
	{
		sign = -1.;
		++i;
	}
	else if (str[i] == '+')
		++i;
	while (ft_isdigit(str[i]))
		res = res * 10 + str[i++] - '0';
	return (res * sign);
}

static long double	ft_atof_fractional(char *str)
{
	long double	res;

	res = ft_atof_integer(str);
	while (ft_isdigit(*str))
	{
		str++;
		res /= 10.0;
	}
	return (res);
}

static void			skip_digits(char **str)
{
	char *tmp;

	tmp = *str;
	while (ft_isdigit(*tmp))
		++tmp;
	*str = tmp;
}

long double			ft_atof(char *str)
{
	long double	res;
	int			sign;

	sign = 1;
	if (!ft_isdigit(*str) && *str != '-' && *str != '+')
		return (0. / 0.);
	res = (long double)ft_atof_integer(str);
	if (*str == '-' || *str == '+')
		sign = (*(str++) == '-' ? -1 : 1);
	skip_digits(&str);
	if (*str == '.')
	{
		if (!ft_isdigit(*(++str)))
			return (0. / 0.);
		res += (double)sign * ft_atof_fractional(str);
		skip_digits(&str);
	}
	if (*str == 'e' || *str == 'E')
	{
		++str;
		if (!ft_isdigit(*str) && *str != '-' && *str != '+')
			return (0. / 0.);
		res = res * pow(10., (double)ft_atoi(str));
	}
	return (res);
}
