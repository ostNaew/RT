/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paraboloid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 16:04:33 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/24 17:20:51 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

int	get_paraboloid(t_json json, t_paraboloid *paraboloid)
{
	t_json	property;
	double	k;
	double	height;

	property = json_value_by_key(json, "k");
	if (property.type != JSON_NUMBER || property.value.number <= 0)
		return (-1);
	k = (double)property.value.number;
	property = json_value_by_key(json, "height");
	if ((property.type != JSON_NUMBER || property.value.number <= 0) &&
			property.type != JSON_NULL)
		return (-1);
	height = property.type != JSON_NULL ?
					(double)property.value.number : 1. / 0.;
	*paraboloid = new_paraboloid(height, k);
	return (0);
}

int	transform_paraboloid(t_json json, t_paraboloid *paraboloid)
{
	t_json		property;
	t_vector	position;
	t_vector	direction;
	t_4x4matrix	rotation;

	property = json_value_by_key(json, "direction");
	if (property.type != JSON_NULL)
	{
		direction = json2vec(property, 0);
		if (!is_valid_vector(direction))
			return (-1);
		paraboloid->direction = direction;
	}
	property = json_value_by_key(json, "rotation");
	if (get_rotation_matrix(property, &rotation))
		return (-1);
	*paraboloid = transform_paraboloid_ws(*paraboloid, rotation);
	property = json_value_by_key(json, "position");
	position = json2vec(property, 1);
	if (!is_valid_vector(position))
		return (-1);
	paraboloid->position = position;
	return (0);
}

int	add_paraboloids_values(void **primitive, t_json json)
{
	t_paraboloid	paraboloid;

	if (get_paraboloid(json, &paraboloid))
		return (-1);
	if (transform_paraboloid(json, &paraboloid))
		return (-1);
	*primitive = malloc(sizeof(t_paraboloid));
	((t_paraboloid*)(*primitive))[0] = paraboloid;
	return (0);
}
