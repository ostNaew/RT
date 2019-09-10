/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_null.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:53:00 by ejommy            #+#    #+#             */
/*   Updated: 2019/02/28 20:40:23 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_internal.h"

t_json	parse_null(char **json_string, int *status)
{
	t_json	res;

	*status = 0;
	res = new_json();
	res.type = JSON_NULL;
	if (!ft_strnequ("null", *json_string, 4))
		*status = -1;
	*json_string += 4;
	return (res);
}
