/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:31:23 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/13 15:20:08 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

int	get_cone(t_json json, t_cone *cone)
{
	t_json	property;
	double	angle;
	double	height;

	property = json_value_by_key(json, "angle");
	if (property.type != JSON_NUMBER || property.value.number <= 0)
		return (-1);
	angle = (double)property.value.number * M_PI / 180.;
	property = json_value_by_key(json, "height");
	if ((property.type != JSON_NUMBER || property.value.number <= 0) &&
			property.type != JSON_NULL)
		return (-1);
	height = property.type != JSON_NULL ?
					(double)property.value.number : 1. / 0.;
	*cone = new_cone(height, angle);
	return (0);
}

int	transform_cone(t_json json, t_cone *cone)
{
	t_json		property;
	t_vector	tip;
	t_vector	direction;
	t_4x4matrix	rotation;

	property = json_value_by_key(json, "tip");
	tip = json2vec(property, 1);
	if (!is_valid_vector(tip))
		return (-1);
	cone->tip = tip;
	property = json_value_by_key(json, "direction");
	if (property.type != JSON_NULL)
	{
		direction = json2vec(property, 0);
		if (!is_valid_vector(direction))
			return (-1);
		cone->direction = direction;
	}
	property = json_value_by_key(json, "rotation");
	if (get_rotation_matrix(property, &rotation))
		return (-1);
	*cone = transform_cone_ws(*cone, rotation);
	return (0);
}

int	add_cones_values(void **primitive, t_json json)
{
	t_cone	cone;

	if (get_cone(json, &cone))
		return (-1);
	if (transform_cone(json, &cone))
		return (-1);
	*primitive = malloc(sizeof(t_cone));
	((t_cone*)(*primitive))[0] = cone;
	return (0);
}
