/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:39:44 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/01 15:06:22 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_internal.h"

static int	ft_get_boolean(char **str)
{
	if (ft_strnequ("true", *str, 4))
	{
		*str += 4;
		return (1);
	}
	if (ft_strnequ("false", *str, 5))
	{
		*str += 5;
		return (0);
	}
	return (-1);
}

t_json		parse_bool(char **json_string, int *status)
{
	t_json	res;

	*status = 0;
	res = new_json();
	res.type = JSON_BOOL;
	res.value.boolean = ft_get_boolean(json_string);
	if (res.value.boolean == -1)
		*status = -1;
	return (res);
}
