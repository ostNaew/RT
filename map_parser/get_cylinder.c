/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:38:10 by ejommy            #+#    #+#             */
/*   Updated: 2019/03/13 15:19:49 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

int	get_cylinder(t_json json, t_cylinder *cylinder)
{
	t_json	property;
	double	radius;
	double	height;

	property = json_value_by_key(json, "radius");
	if (property.type != JSON_NUMBER || property.value.number <= 0)
		return (-1);
	radius = (double)property.value.number;
	property = json_value_by_key(json, "height");
	if ((property.type != JSON_NUMBER || property.value.number <= 0) &&
			property.type != JSON_NULL)
		return (-1);
	height = property.type != JSON_NULL ?
					(double)property.value.number : 1. / 0.;
	*cylinder = new_cylinder(height, radius);
	return (0);
}

int	transform_cylinder(t_json json, t_cylinder *cylinder)
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
		cylinder->direction = direction;
	}
	property = json_value_by_key(json, "rotation");
	if (get_rotation_matrix(property, &rotation))
		return (-1);
	*cylinder = transform_cylinder_ws(*cylinder, rotation);
	property = json_value_by_key(json, "position");
	position = json2vec(property, 1);
	if (!is_valid_vector(position))
		return (-1);
	cylinder->position = position;
	return (0);
}

int	add_cylinders_values(void **primitive, t_json json)
{
	t_cylinder	cylinder;

	if (get_cylinder(json, &cylinder))
		return (-1);
	if (transform_cylinder(json, &cylinder))
		return (-1);
	*primitive = malloc(sizeof(t_cylinder));
	((t_cylinder*)(*primitive))[0] = cylinder;
	return (0);
}
