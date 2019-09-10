/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:01:11 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/13 13:59:13 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	atoi_hex(char *str)
{
	int		res;
	char	*base;

	res = 0;
	base = "0123456789abcdef";
	while (ft_isspace(*str))
		str++;
	if (str[0] != '0' || ft_tolower(str[1]) != 'x')
		return (0);
	str += 2;
	while (*str)
	{
		res = res * 16 + (ft_strchr(base, ft_tolower(*str)) - base);
		str++;
	}
	return (res);
}
