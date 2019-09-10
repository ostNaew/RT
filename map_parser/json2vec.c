/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json2vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:31:02 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/03 19:25:23 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

t_vector	object2vector(t_json json)
{
	t_vector	res;
	t_json		property;

	res = (t_vector){0. / 0., 0. / 0., 0. / 0., 0. / 0.};
	property = json_value_by_key(json, "x");
	if (property.type != JSON_NUMBER)
		return (res);
	res.x = property.value.number;
	property = json_value_by_key(json, "y");
	if (property.type != JSON_NUMBER)
		return (res);
	res.y = property.value.number;
	property = json_value_by_key(json, "z");
	if (property.type != JSON_NUMBER)
		return (res);
	res.z = property.value.number;
	return (res);
}

t_vector	array2vector(t_json json)
{
	t_vector	res;
	t_json		property;

	res = (t_vector){0. / 0., 0. / 0., 0. / 0., 0. / 0.};
	property = json_value_by_index(json, 0);
	if (property.type != JSON_NUMBER)
		return (res);
	res.x = property.value.number;
	property = json_value_by_index(json, 1);
	if (property.type != JSON_NUMBER)
		return (res);
	res.y = property.value.number;
	property = json_value_by_index(json, 2);
	if (property.type != JSON_NUMBER)
		return (res);
	res.z = property.value.number;
	return (res);
}

t_vector	json2vec(t_json json, int w)
{
	t_vector	res;

	res = (t_vector){0. / 0., 0. / 0., 0. / 0., 0. / 0.};
	if ((json.type != JSON_OBJECT && json.type != JSON_ARRAY) || json.size != 3)
		return (res);
	if (json.type == JSON_OBJECT)
		res = object2vector(json);
	else if (json.type == JSON_ARRAY)
		res = array2vector(json);
	res.w = (double)w;
	return (res);
}
