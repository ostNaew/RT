/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 20:25:19 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/02 15:38:17 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_internal.h"

void	json_destroy(t_json *json)
{
	size_t	i;

	if (json)
	{
		ft_memdel((void*)&json->key);
		if (json->type == JSON_STRING)
			free(json->value.string);
		else if (json->type == JSON_ARRAY || json->type == JSON_OBJECT)
		{
			i = -1;
			while (++i < json->size)
				json_destroy((json->type == JSON_ARRAY) ?
						&json->value.array[i] : &json->value.object[i]);
			free((json->type == JSON_ARRAY) ?
					json->value.array : json->value.object);
		}
		json->type = JSON_NULL;
	}
}
