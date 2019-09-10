/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:29:17 by ejommy            #+#    #+#             */
/*   Updated: 2019/02/28 20:40:44 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_internal.h"

t_json	parse_string(char **json_string, int *status)
{
	t_json	res;

	*status = 0;
	res = new_json();
	res.type = JSON_STRING;
	skip_spaces(json_string);
	if (!(res.value.string = get_string(json_string)))
		*status = -1;
	return (res);
}
