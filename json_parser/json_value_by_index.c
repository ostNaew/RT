/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_value_by_index.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:58:48 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/01 18:07:18 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"

t_json	json_value_by_index(t_json json, size_t index)
{
	if (json.type == JSON_ARRAY && index < json.size)
		return (json.value.array[index]);
	return (new_json());
}
