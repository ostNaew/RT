/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:26:40 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/01 17:17:35 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_internal.h"

t_json	parse_element(char **json_string, int *status)
{
	t_json	elem;

	elem = new_json();
	if (**json_string == '"')
		elem = parse_string(json_string, status);
	else if (ft_isdigit(**json_string) || **json_string == '-' ||
			**json_string == '+')
		elem = parse_number(json_string, status);
	else if (**json_string == 't' || **json_string == 'f')
		elem = parse_bool(json_string, status);
	else if (**json_string == 'n')
		elem = parse_null(json_string, status);
	else if (**json_string == '[')
		elem = parse_array(json_string, status);
	else if (**json_string == '{')
		elem = parse_object(json_string, status);
	else
		*status = -1;
	return (elem);
}
