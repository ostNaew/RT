/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:44:06 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/01 15:33:59 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_internal.h"

static void	iterate_str(char **json_string)
{
	char	*str;

	str = *json_string;
	if (*str == '-' || *str == '+')
		++str;
	while (ft_isdigit(*str))
		++str;
	if (*str == '.')
	{
		++str;
		while (ft_isdigit(*str))
			++str;
	}
	if (*str == 'e' || *str == 'E')
	{
		++str;
		if (*str == '-' || *str == '+')
			++str;
		while (ft_isdigit(*str))
			++str;
	}
	*json_string = str;
}

t_json		parse_number(char **json_string, int *status)
{
	t_json	res;

	*status = 0;
	res = new_json();
	res.type = JSON_NUMBER;
	res.value.number = ft_atof(*json_string);
	if (isnan(res.value.number))
		*status = -1;
	iterate_str(json_string);
	return (res);
}
