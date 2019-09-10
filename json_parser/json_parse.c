/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:23:05 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/02 15:39:42 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_internal.h"

t_json	json_parse(char *json_string)
{
	t_json	res;
	char	*tmp;
	int		status;

	res = new_json();
	if (json_string)
	{
		json_string = ft_strtrim(json_string);
		if ((tmp = json_string))
		{
			res = parse_element(&tmp, &status);
			if (*tmp || status != 0)
				json_destroy(&res);
		}
		free(json_string);
	}
	return (res);
}
