/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_value_by_key.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:03:27 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/02 15:43:51 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_internal.h"

t_json	json_value_by_key(t_json json, char *key)
{
	size_t	i;

	i = -1;
	if (json.type == JSON_OBJECT && key)
		while (++i < json.size)
			if (ft_strequ(json.value.object[i].key, key))
				return (json.value.object[i]);
	return (new_json());
}
